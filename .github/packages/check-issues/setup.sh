#!/bin/bash
set -euo pipefail

apt update

apt install -y --no-install-recommends \
    libclang-dev

cargo install --path /input/tools/issues

apt autoremove -y
apt clean
rm -rf /var/lib/apt/lists/*
