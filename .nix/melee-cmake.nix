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
}:
assert dwarf -> newlib != null;
(if dwarf then stdenvNoCC else stdenv).mkDerivation {
  name = "melee-cmake" + lib.optionalString dwarf "-dwarf";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions [
      ../CMakeLists.txt
      ../cmake
      ../src/sysdolphin
      ../src/melee
      ../src/Runtime
      ../src/placeholder.h
      ../src/m2c_macros.h
    ];
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
  ];

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
