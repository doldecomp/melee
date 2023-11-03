#!/bin/sh
set -e

git clone /input /tmp/input
cd /tmp/input
ln -s /opt/mwcc_compiler tools/

. /opt/venv/bin/activate
pip install --no-cache-dir -r requirements.txt

make -j"$(nproc)" WINE="$WINE" GENERATE_MAP=1 MAX_ERRORS=1
cp build/ssbm.us.1.2/GALE01.map /output/
python tools/parse_map.py
dadosod dol build/ssbm.us.1.2/main.dol \
    -m build/map.csv \
    -o /output
