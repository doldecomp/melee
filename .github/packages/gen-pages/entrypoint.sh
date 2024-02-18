#!/bin/bash
set -euo pipefail

git clone /input /tmp/input
cd /tmp/input
ln -s /opt/mwcc_compiler tools/

cp -R /opt/venv .venv
. .venv/bin/activate
pip install --no-cache-dir -r requirements.txt

mkdir -p build/doxygen
doxygen Doxyfile
touch build/doxygen/html/.nojekyll
python tools/m2ctx/m2ctx.py -pqr
melee-mwcc build/ctx.c -v -o build/ctx.c.o
cp build/ctx.html build/doxygen/html/
cp -r build/doxygen/html/* /output
