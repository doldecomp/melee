#!/bin/sh
set -e

git clone /input /tmp/input
cd /tmp/input
ln -s /opt/mwcc_compiler tools/

. /opt/venv/bin/activate
pip install --no-cache-dir -r requirements.txt

mkdir -p build/doxygen
doxygen Doxyfile
touch build/doxygen/html/.nojekyll
python tools/m2ctx/m2ctx.py -pqr
melee-mwcc build/ctx.c -v -o build/ctx.c.o
make -j"$(nproc)" WINE="$WINE" GENERATE_MAP=1 MAX_ERRORS=1
mkdir build/doxygen/html/dump
cp build/ssbm.us.1.2/GALE01.map build/doxygen/html/dump/
python tools/parse_map.py
dadosod dol build/ssbm.us.1.2/main.dol \
    -m build/map.csv \
    -o build/doxygen/html/dump
python tools/dump_tree.py \
    build/doxygen/html/dump \
    build/doxygen/html/dump/index.html
cp build/ctx.html build/doxygen/html/
cp -r build/doxygen/html/* /output
