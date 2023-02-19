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

FROM sid AS setup-devkitpro
RUN sudo dpkg --add-architecture i386
RUN sudo apt update
RUN sudo apt install \
    build-essential \
    gcc-multilib \
    g++-multilib \
    libc6:i386 \
    lsb-release

FROM setup-devkitpro AS setup-wibo
WORKDIR /tmp
RUN git clone https://github.com/decompals/wibo.git --depth=1
WORKDIR /tmp/wibo
RUN cmake -B build
RUN cmake --build build
RUN chmod +x build/wibo
RUN cp build/wibo /usr/local/bin
ENV WINE /usr/local/bin/wibo

FROM setup-wibo AS setup-mwcc
WORKDIR /tmp
RUN git clone https://github.com/doldecomp/melee.git --depth=1
WORKDIR /tmp/melee
RUN curl -L \
    'https://cdn.discordapp.com/attachments/727918646525165659/917185027656286218/GC_WII_COMPILERS.zip' \
    | bsdtar -xvf- -C tools --exclude Wii
RUN mv tools/GC tools/mwcc_compiler
RUN sha1sum -c tools/mwld_prepatch.sha1
RUN python3 tools/mwld_patch.py
RUN sha1sum -c tools/mwld_postpatch.sha1
RUN cp -a tools/mwcc_compiler /usr/local/bin/
RUN printf "%s\n" \
    '#!/bin/sh'\
    '$WINE /usr/local/bin/mwcc_compiler/1.2.5e/mwcceppc.exe "$@"' \
    >/usr/local/bin/mwcceppc
RUN chmod +x /usr/local/bin/mwcceppc

FROM setup-mwcc AS setup-devenv
RUN sudo apt install \
    python3-full
RUN python3 -m venv /usr/local/share/venv
RUN . /usr/local/share/venv/bin/activate; \
    pip3 install -r requirements.txt
RUN mkdir -p /usr/local/src/melee
ENV PATH="/src/melee/tools:${PATH}"
RUN rm -rf /tmp/*
WORKDIR /usr/local/src
