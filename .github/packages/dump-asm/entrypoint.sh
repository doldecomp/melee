#!/bin/bash
set -euox pipefail

git clone /input /tmp/input
cd /tmp/input
ln -s /opt/mwcc_compiler tools/

make -j"$(nproc)" WINE="$WINE" GENERATE_MAP=1 MAX_ERRORS=1

. /opt/venv/bin/activate
pip install --no-cache-dir -r requirements.txt

cp build/ssbm.us.1.2/GALE01.map /output/

readme.py >/output/README.md

python tools/parse_map.py
python tools/m2ctx/m2ctx.py -pn \
    >/output/ctx.c
dadosod dol build/ssbm.us.1.2/main.dol \
    -m build/map.csv \
    -o /output
