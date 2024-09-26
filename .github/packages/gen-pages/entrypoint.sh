#!/usr/bin/env bash
set -euox pipefail

git clone /input /tmp/input
cd /tmp/input
ln -s /opt/mwcc_compiler tools/

cp -R /opt/venv .venv
. .venv/bin/activate
pip install --no-cache-dir -r reqs/gen-pages.txt

touch /output/.nojekyll

mkdir build

mkdir build/doxygen
doxygen Doxyfile
cp -R build/doxygen/html/* /output

python tools/m2ctx/m2ctx.py -pqr
melee-mwcc build/ctx.c -v -o build/ctx.o
cp build/ctx.html /output/

# Progress site

mkdir /output/progress
cp tools/progress-redirect.html /output/progress/index.html
