#!/bin/sh

set +x
HERE=$(dirname "$(readlink -f $0)")

pushd $HERE/.. > /dev/null

find src -type f -name "*.h" | \
  sed -r -e 's/((src\/MSL|src)\/)?(.*)/#include <\3>/' \
  > build/ctx_includes.h

python tools/m2ctx/m2ctx.py build/ctx_includes.h \
  | clang-format

popd > /dev/null
