#!/usr/bin/env bash
set -euox pipefail

apt update

function install {
    apt install -y --no-install-recommends "${@}"
}

install curl ca-certificates

curl -L https://deb.nodesource.com/setup_20.x | bash -

install \
    doxygen \
    git \
    libarchive-tools \
    nodejs \
    python-is-python3 \
    python3-full

# Acquire external assets
git clone --no-checkout --depth=1 \
    'https://github.com/doldecomp/assets.git' \
    /tmp/assets
pushd /tmp/assets
git sparse-checkout init --cone
git sparse-checkout set melee
git checkout
mv melee /opt/assets
popd

# Acquire fonts
fonts_url='https://media.fontsgeek.com/download/zip/a/-/a-otf-folk-pro_WeXVg.zip'
curl -L "$fonts_url" |
    bsdtar -xvf- -C /tmp
mv '/tmp/A-OTF Folk Pro/A-OTF Folk Pro H/A-OTF Folk Pro H.otf' \
    '/opt/assets/progress'

# Install progress site node modules
pushd /tmp
npm install --no-audit --no-progress
mv node_modules /opt
popd

# Create and update Python venv
python -m venv --upgrade-deps /opt/venv
. /opt/venv/bin/activate
pip install --no-cache-dir -r /tmp/requirements.txt

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
npm cache clean --force
rm -rf /var/lib/apt/lists/*
rm -rf /tmp/*
