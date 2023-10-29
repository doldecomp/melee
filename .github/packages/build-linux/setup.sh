#!/bin/sh
set -e

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
    megatools \
    libarchive-tools \

# Create and update Python venv
python -m venv --upgrade-deps /opt/venv
. /opt/venv/bin/activate
pip install --no-cache-dir -r /tmp/requirements.txt

# Install melee compiler
megadl --no-progress "$MELEE_COMPILERS_URL" --path - |
    bsdtar -xvf- -C /tmp
mv /tmp/GC /tmp/mwcc_compiler
mv /tmp/mwcc_compiler /opt

apt remove -y \
    megatools \
    libarchive-tools
apt autoremove -y
apt clean
rm -rf /var/lib/apt/lists/*
