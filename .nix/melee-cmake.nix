{
  stdenv,
  lib,
  cmake,
  aurora-src,
}:
stdenv.mkDerivation {
  name = "melee-cmake";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions [
      ../CMakeLists.txt
      ../src/sysdolphin
      ../src/melee
      ../src/Runtime
      ../src/placeholder.h
      ../src/m2c_macros.h
    ];
  };

  nativeBuildInputs = [
    cmake
  ];

  makeFlags = [ "-k" ];

  env.AURORA_SRC = "${aurora-src}";

  __structuredAttrs = true;
}
