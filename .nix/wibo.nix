{
  stdenv,
  lib,
  mimalloc,
  cmake,
  src,
}:

stdenv.mkDerivation (finalAttrs: {
  pname = "wibo";
  version = src.shortRev;
  inherit src;

  patches = [
    ./wibo-no-case-insensitive.patch
  ];

  nativeBuildInputs = [
    cmake
  ];

  buildInputs = [
    mimalloc
  ];

  cmakeFlags = [
    "-DFETCHCONTENT_TRY_FIND_PACKAGE_MODE=ALWAYS"
  ];

  meta = with lib; {
    description = "Quick-and-dirty wrapper to run 32-bit windows EXEs on linux";
    longDescription = ''
      A minimal, low-fuss wrapper that can run really simple command-line
      32-bit Windows binaries on Linux - with less faff and less dependencies
      than WINE.
    '';
    homepage = "https://github.com/decompals/WiBo";
    license = licenses.mit;
    maintainers = with maintainers; [ r-burns ];
    platforms = [ "i686-linux" ];
    mainProgram = "wibo";
  };

  # HACK: sjiswrap triggers buffer overflow detection, is this spurious?
  hardeningDisable = [ "fortify" ];
})
