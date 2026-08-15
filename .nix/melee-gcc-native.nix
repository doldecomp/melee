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
      ../src/Runtime
    ];
  };

  postPatch = ''
    cp ${./CMakeLists.txt} CMakeLists.txt
  '';

  nativeBuildInputs = [
    cmake
  ];

  env.AURORA_SRC = aurora-src;

  __structuredAttrs = true;
}
