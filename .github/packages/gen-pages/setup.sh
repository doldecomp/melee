#!/usr/bin/env bash
set -euox pipefail

apt update

apt install -y --no-install-recommends \
    ca-certificates \
    curl \
    doxygen \
    git \
    libarchive-tools \
    python-is-python3 \
    python3-full

# Create and update Python venv
python -m venv --upgrade-deps /opt/venv
. /opt/venv/bin/activate
pip install --no-cache-dir -r /tmp/reqs/gen-pages.txt

# Install melee compiler (for checking ctx.c)
curl -L "$MELEE_COMPILERS_URL" |
    bsdtar -xvf- -C /tmp
mv /tmp/GC /tmp/mwcc_compiler
mv /tmp/mwcc_compiler /opt

# Clean up
apt remove -y \
    libarchive-tools
apt autoremove -y
apt clean
rm -rf /var/lib/apt/lists/*
rm -rf /tmp/*
