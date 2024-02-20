#!/usr/bin/env bash
set -euox pipefail

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

# Progress site
cd /tmp/input/tools/progress-site

src='/opt/assets/progress'
static='static/extern'
lib='src/lib/extern'

# assets
for file in "$src"/*; do
    if [[ $(basename "$file") == 'favicon.png' ]]; then
        dst="$static"
    else
        dst="$lib"
    fi
    cp "$file" "$dst"
done

# progress
# BUG race condition between `build-melee` and `gen-pages`.
progress_url='https://progress.decomp.club/data/melee/GALE01?format=json&mode=all'
curl -s -L "$progress_url" -o "$lib/progress.json"

# install
cp -R /opt/node_modules .
export npm_config_cache='npm-cache'
npm install \
    --no-audit \
    --no-progress \
    --prefer-offline

# build
npm run build
find build -type f -name '.gitkeep' -delete
mv build /output/progress
