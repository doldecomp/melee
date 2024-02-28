{ lib
, stdenv
, fetchFromGitHub
, cmake
}:

stdenv.mkDerivation rec {
  pname = "wibo";
  version = "0.6.12";

  src = fetchFromGitHub {
    owner = "decompals";
    repo = "wibo";
    rev = version;
    hash = "sha256-Kv3jbyWouz/bmteaoJyKkFC5YWuTEEaY6OvmJbZ0Xfg=";
  };

  nativeBuildInputs = [
    cmake
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
