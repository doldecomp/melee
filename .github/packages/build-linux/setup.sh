#!/usr/bin/env bash
set -euox pipefail

apt update

apt install -y --no-install-recommends \
    ca-certificates \
    curl \
    gcc \
    git \
    libarchive-tools \
    libc6-dev \
    make \
    python-is-python3 \
    python3-minimal

# Install melee compiler
curl -L "$MELEE_COMPILERS_URL" |
    bsdtar -xvf- -C /tmp
mv /tmp/GC /tmp/mwcc_compiler
mv /tmp/mwcc_compiler /opt

# Install binutils
dst="$DEVKITPPC/bin"
mkdir -p "$dst"
curl -L "$BINUTILS_URL" |
    bsdtar -xvf- -C /tmp
src='/tmp/powerpc-eabi-as'
chmod +x "$src"
mv "$src" "$dst"

# Clean up
apt remove -y \
    libarchive-tools
apt autoremove -y
apt clean
rm -rf /var/lib/apt/lists/*
rm -rf /tmp/*
