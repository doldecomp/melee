{ lib
, stdenv
, decomp-toolkit
, fetchurl
, mwcc
, ninja
, python3
, wibo
}:
let
  sjiswrap = fetchurl {
    url = "https://github.com/encounter/sjiswrap/releases/download/v1.2.1/sjiswrap-windows-x86.exe";
    hash = "sha256-6GMMjcxhTSKzFmS6MyQvEkO7m+T91ATtbDXYt9pI8hk=";
  };
in
stdenv.mkDerivation {
  name = "doldecomp-melee";

  src = lib.cleanSourceWith {
    filter = name: type: let
      basename = baseNameOf (toString name);
    in !(false
      || basename == "build"
      || basename == "expected"
      || lib.hasSuffix ".nix" basename
      || lib.hasSuffix ".dump" basename
      || lib.hasSuffix ".o" basename
    );
    src = lib.cleanSource ../.;
  };

  postPatch = ''
    ln -sfT ${mwcc}/GC tools/mwcc_compiler
  '';

  shellHook = ''
    runHook postPatch
  '';

  nativeBuildInputs = [
    decomp-toolkit
    ninja
    python3
    wibo
  ];

  configurePhase = ''
    runHook preConfigure
    python3 ./configure.py --wrapper ${wibo}/bin/wibo \
      --dtk ${decomp-toolkit}/bin/dtk \
      --sjiswrap ${sjiswrap} \
      --compilers ${mwcc}
    runHook postConfigure
  '';

  enableParallelBuilding = true;

  installPhase = ''
    runHook preInstall
    mkdir -p $out
    cp build/GALE01/main.dol $out/
    runHook postInstall
  '';
}
