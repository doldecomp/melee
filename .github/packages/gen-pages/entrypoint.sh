#!/bin/sh
set -e

git clone /input /tmp/input
cd /tmp/input

. /opt/venv/bin/activate
pip install --no-cache-dir -r requirements.txt

mkdir -p build/doxygen
ln -s /opt/doxygen-awesome-css tools/
doxygen Doxyfile
touch build/doxygen/html/.nojekyll
python tools/m2ctx/m2ctx.py -pqr
cp build/ctx.html build/doxygen/html/
cp -r build/doxygen/html/* /output
