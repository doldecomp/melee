{ lib
, stdenv
, fetchFromGitHub
, mimalloc
, cmake
}:

stdenv.mkDerivation rec {
  pname = "wibo";
  version = "0.7.0";

  src = fetchFromGitHub {
    owner = "decompals";
    repo = "wibo";
    rev = version;
    hash = "sha256-PEqfvpS3p8Zooee7k59SN2UiSZWfITuB/VULIrfup4w=";
  };

  nativeBuildInputs = [
    cmake
  ];

  buildInputs = [
    mimalloc
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
}
