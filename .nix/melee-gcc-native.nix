{
  lib,
  stdenv,
  cmake,
  aurora-src,
}:
stdenv.mkDerivation {
  name = "melee-gcc-native";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions [
      ../src/sysdolphin
      ../src/melee
      ../src/Runtime
      ../src/placeholder.h
      ../src/m2c_macros.h
    ];
  };

  postPatch = ''
    cp ${./CMakeLists.txt} CMakeLists.txt
  '';

  nativeBuildInputs = [
    cmake
  ];

  env.AURORA_SRC = aurora-src;
  env.CFLAGS = ''
    -fmax-errors=0
  '';

  __structuredAttrs = true;
}
