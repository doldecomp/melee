#!/usr/bin/env bash
set -euox pipefail

apt update

apt install -y --no-install-recommends \
    git \
    doxygen \
    python3-full \
    python-is-python3 \
    git \
    make \
    gcc \
    libc6-dev \
    python3-full \
    python-is-python3 \
    curl \
    libarchive-tools

# Create and update Python venv
python -m venv --upgrade-deps /opt/venv
. /opt/venv/bin/activate
pip install --no-cache-dir -r /tmp/requirements.txt

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
