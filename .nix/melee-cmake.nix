{
  stdenv,
  stdenvNoCC,
  lib,
  cmake,
  ninja,
  llvmPackages_22,
  aurora-src,
  # Build for the original 32-bit big-endian PowerPC ABI and emit DWARF
  # describing its type layouts; mirrors the ppc-dwarf CMake preset
  dwarf ? false,
  # powerpc-none-eabi newlib, used only for its libc headers
  newlib ? null,
  # Also sample the .dat archives' types (cmake/Dat.cmake): the melee-dat
  # tool and the game's files
  melee-dat ? null,
  dat-files ? null,
}:
let
  withDat = dat-files != null;
in
assert dwarf -> newlib != null;
assert withDat -> dwarf && melee-dat != null;
(if dwarf then stdenvNoCC else stdenv).mkDerivation {
  name = "melee-cmake" + lib.optionalString dwarf "-dwarf" + lib.optionalString withDat "-dat";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions (
      [
        ../CMakeLists.txt
        ../cmake
        ../src/sysdolphin
        ../src/melee
        ../src/Runtime
        ../libs/doldecomp
      ]
      ++ lib.optionals withDat [
        ../config
        ../.clang-format
      ]
    );
  };

  nativeBuildInputs = [
    cmake
  ]
  ++ lib.optionals dwarf [
    ninja
    llvmPackages_22.clang-unwrapped
    llvmPackages_22.bintools-unwrapped
  ];

  makeFlags = lib.optionals (!dwarf) [ "-k" ];

  cmakeBuildType = if dwarf then "Debug" else "Release";

  cmakeFlags = lib.optionals dwarf [
    (lib.cmakeBool "MELEE_DWARF" true)
    (lib.cmakeFeature "NEWLIB_INCLUDE" "${newlib}/powerpc-none-eabi/include")
  ]
  ++ lib.optionals withDat [
    (lib.cmakeBool "MELEE_DAT_SAMPLES" true)
    (lib.cmakeFeature "MELEE_DAT" "${melee-dat}/bin/melee-dat")
    (lib.cmakeFeature "MELEE_DAT_FILES" "${dat-files}")
  ];

  # The samples' objdiff project, as built
  postInstall = lib.optionalString withDat ''
    mkdir -p $out/dat
    cp -r target src base objdiff.json $out/dat
  '';

  preConfigure = lib.optionalString dwarf ''
    appendToVar cmakeFlags "-DCMAKE_TOOLCHAIN_FILE=$PWD/cmake/ppc32-clang.cmake"
  '';

  # The debug information is the point of this build
  dontStrip = dwarf;
  dontFixup = dwarf;

  env = {
    AURORA_SRC = "${aurora-src}";
  }
  // lib.optionalAttrs dwarf {
    # nixpkgs' cmake hook passes these through as CMAKE_AR/CMAKE_RANLIB
    AR = "llvm-ar";
    RANLIB = "llvm-ranlib";
  };

  __structuredAttrs = true;
}
