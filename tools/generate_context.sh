#!/usr/bin/env bash

set +ex
HERE=$(dirname "$(readlink -f $0)")

pushd $HERE/.. > /dev/null

find src -type f -name "*.h" | \
  sed -r -e 's/((src\/MSL|src)\/)?(.*)/#include <\3>/' \
  > build/ctx_includes.h

output=$(python3 tools/m2ctx/m2ctx.py build/ctx_includes.h)

if [ -x "$(command -v clang-format)" ]; then
  output=$(echo "$output" | clang-format)
fi

echo "$output" | tee build/ctx.c

popd > /dev/null
