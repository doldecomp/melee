#!/bin/sh
set -e

apt update

apt install -y --no-install-recommends \
    git \
    make \
    gcc \
    libc6-dev \
    python3-full \
    python-is-python3 \
    curl \
    libarchive-tools

curl -L "$MELEE_COMPILERS_URL" |
    bsdtar -xvf- -C /tmp
mv /tmp/GC /tmp/mwcc_compiler
mv /tmp/mwcc_compiler /opt

apt remove -y \
    curl \
    libarchive-tools
apt autoremove -y
apt clean
rm -rf /var/lib/apt/lists/*
