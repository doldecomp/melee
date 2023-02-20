FROM devkitpro/devkitppc:20230110 AS buster
ENV DEBIAN_FRONTEND noninteractive
ENV LC_ALL C
RUN printf '%s;\n' \
    'APT::Cmd::Disable-Script-Warning "true"' \
    'APT::Get::Assume-Yes "true"' \
    >> /etc/apt/apt.conf.d/99disable-scripts && \
    sudo apt update && \
    sudo apt autoremove

FROM buster AS bullseye
RUN printf '%s\n' \
    'deb http://http.us.debian.org/debian bullseye main contrib non-free' \
    'deb-src http://http.us.debian.org/debian bullseye main contrib non-free' \
    > /etc/apt/sources.list && \
    sudo apt update && \
    sudo apt dist-upgrade && \
    sudo apt autoremove

FROM bullseye AS bookworm
RUN printf '%s\n' \
    'deb http://http.us.debian.org/debian bookworm main contrib non-free' \
    'deb-src http://http.us.debian.org/debian bookworm main contrib non-free' \
    > /etc/apt/sources.list && \
    sudo apt update && \
    sudo apt dist-upgrade && \
    sudo apt autoremove

FROM bookworm AS install-packages
RUN sudo dpkg --add-architecture i386 && \
    sudo apt update && \
    sudo apt install \
    build-essential \
    ninja-build \
    gcc-multilib \
    g++-multilib \
    libc6:i386 \
    lsb-release \
    neofetch \
    python3-full \
    nodejs \
    npm

FROM install-packages AS setup-wibo
RUN mkdir -p /tmp/wibo && \
    cd /tmp/wibo && \
    git clone https://github.com/decompals/wibo.git --depth=1 -- . && \
    cmake -B build && \
    cmake --build build && \
    chmod +x build/wibo && \
    cp build/wibo /usr/local/bin && \
    cd / && \
    rm -rf /tmp/*
ENV WINE /usr/local/bin/wibo

FROM setup-wibo AS setup-melee
RUN git clone https://github.com/doldecomp/melee.git --depth=1 -- /usr/local/src/melee
WORKDIR /usr/local/src/melee
ENV PATH="/usr/local/src/melee/tools:${PATH}"

FROM setup-melee AS setup-mwcc
RUN curl -L \
    'https://cdn.discordapp.com/attachments/727918646525165659/917185027656286218/GC_WII_COMPILERS.zip' | \
    bsdtar -xvf- -C tools --exclude Wii && \
    mv tools/GC tools/mwcc_compiler && \
    sha1sum -c tools/mwld_prepatch.sha1 && \
    python3 tools/mwld_patch.py && \
    sha1sum -c tools/mwld_postpatch.sha1 && \
    cp -a tools/mwcc_compiler /usr/local/bin/ && \
    printf "%s\n" \
    '#!/bin/sh' \
    '$WINE /usr/local/bin/mwcc_compiler/1.2.5e/mwcceppc.exe "$@"' \
    > /usr/local/bin/mwcceppc && \
    chmod +x /usr/local/bin/mwcceppc

FROM setup-mwcc AS setup-venv
RUN python3 -m venv /usr/local/share/venv && \
    . /usr/local/share/venv/bin/activate && \
    pip3 install -r requirements.txt
