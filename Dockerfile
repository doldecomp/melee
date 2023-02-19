FROM devkitpro/devkitppc:latest AS buster

ENV DEBIAN_FRONTEND noninteractive
ENV LC_ALL C
RUN printf '%s;\n' \
    'APT::Cmd::Disable-Script-Warning "true"'\
    'APT::Get::Assume-Yes "true"' \
    >> /etc/apt/apt.conf.d/99disable-scripts
RUN sudo apt update

FROM buster AS bullseye
RUN printf '%s\n' \
    'deb http://http.us.debian.org/debian bullseye main contrib non-free' \
    'deb-src http://http.us.debian.org/debian bullseye main contrib non-free' \
    > /etc/apt/sources.list
RUN sudo apt update
RUN sudo apt dist-upgrade
RUN sudo apt autoremove

FROM bullseye AS bookworm
RUN printf '%s\n' \
    'deb http://http.us.debian.org/debian bookworm main contrib non-free' \
    'deb-src http://http.us.debian.org/debian bookworm main contrib non-free' \
    > /etc/apt/sources.list
RUN sudo apt update
RUN sudo apt dist-upgrade
RUN sudo apt autoremove

FROM bookworm AS sid
RUN printf '%s\n' \
    'deb http://http.us.debian.org/debian sid main contrib non-free' \
    'deb-src http://http.us.debian.org/debian sid main contrib non-free' \
    > /etc/apt/sources.list
RUN sudo apt update
RUN sudo apt dist-upgrade
RUN sudo apt autoremove

FROM sid AS install-packages
RUN sudo dpkg --add-architecture i386
RUN sudo apt update
RUN sudo apt install \
    build-essential \
    ninja-build \
    gcc-multilib \
    g++-multilib \
    libc6:i386 \
    lsb-release \
    python3-full

FROM install-packages AS setup-wibo
WORKDIR /tmp
RUN git clone https://github.com/decompals/wibo.git --depth=1
WORKDIR /tmp/wibo
RUN cmake -B build
RUN cmake --build build
RUN chmod +x build/wibo
RUN cp build/wibo /usr/local/bin
ENV WINE /usr/local/bin/wibo
WORKDIR /
RUN rm -rf /tmp/*

FROM setup-wibo AS setup-melee
RUN mkdir -p /usr/local/src/melee
WORKDIR /usr/local/src/melee
RUN git clone https://github.com/doldecomp/melee.git --depth=1 .
ENV PATH="/usr/local/src/melee/tools:${PATH}"

FROM setup-melee AS setup-mwcc
RUN curl -L \
    'https://cdn.discordapp.com/attachments/727918646525165659/917185027656286218/GC_WII_COMPILERS.zip' | \
    bsdtar -xvf- -C tools --exclude Wii && \
    mv tools/GC tools/mwcc_compiler
RUN sha1sum -c tools/mwld_prepatch.sha1 && \
    python3 tools/mwld_patch.py && \
    sha1sum -c tools/mwld_postpatch.sha1 && \
    cp -a tools/mwcc_compiler /usr/local/bin/
RUN printf "%s\n" \
    '#!/bin/sh'\
    '$WINE /usr/local/bin/mwcc_compiler/1.2.5e/mwcceppc.exe "$@"' \
    > /usr/local/bin/mwcceppc
RUN chmod +x /usr/local/bin/mwcceppc

FROM setup-mwcc AS setup-venv
RUN python3 -m venv /usr/local/share/venv
RUN . /usr/local/share/venv/bin/activate && \
    pip3 install -r requirements.txt
