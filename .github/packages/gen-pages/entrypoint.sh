#!/usr/bin/env bash
set -euo pipefail

git clone /input /tmp/input
cd /tmp/input
ln -s /opt/mwcc_compiler tools/

cp -R /opt/venv .venv
. .venv/bin/activate
pip install --no-cache-dir -r requirements.txt

touch /output/.nojekyll

mkdir build

mkdir build/doxygen
doxygen Doxyfile
cp -R build/doxygen/html/* /output

python tools/m2ctx/m2ctx.py -pqr
melee-mwcc build/ctx.c -v -o build/ctx.o
cp build/ctx.html /output/
