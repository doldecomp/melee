#!/bin/sh
set -e

git clone /input /tmp/input
cd /tmp/input
ln -s /opt/mwcc_compiler tools/

echo "$MAKE_FLAGS" |
    xargs make -j"$(nproc)" WINE="$WINE"

if [ -f "build/ssbm.us.1.2/GALE01.map" ]; then
    python tools/calcprogress/calcprogress.py \
        --dol build/ssbm.us.1.2/main.dol \
        --map build/ssbm.us.1.2/GALE01.map \
        --asm-obj-ext .s.o \
        --old-map true \
        >build/PROGRESS.md
fi

cp -r build/* /output
