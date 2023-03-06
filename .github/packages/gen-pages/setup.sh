#!/bin/sh
set -e

apt update

apt install -y --no-install-recommends \
    git \
    doxygen \
    python3-full \
    python-is-python3

python -m venv --upgrade-deps /opt/venv
. /opt/venv/bin/activate
pip install --no-cache-dir -r /tmp/requirements.txt

git clone 'https://github.com/jothepro/doxygen-awesome-css' --depth=1 \
    /opt/doxygen-awesome-css

apt autoremove -y
apt clean
rm -rf /var/lib/apt/lists/*
