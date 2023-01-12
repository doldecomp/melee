HERE=$(dirname "$(readlink -f $0)")

pushd $HERE/..

find src -type f -name "*.h" | sed -r -e 's/((src\/MSL|src)\/)?(.*)/#include <\3>/' > ctx_includes.h
python tools/m2ctx/m2ctx.py ctx_includes.h

popd
