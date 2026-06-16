{ lib
, stdenvNoCC
, decomp-toolkit
, devkitppc
, fetchurl
, mwcc
, objdiff
, ninja
, python3Minimal
, wibo
}:
let
  sjiswrap = fetchurl {
    url = "https://github.com/encounter/sjiswrap/releases/download/v1.2.1/sjiswrap-windows-x86.exe";
    hash = "sha256-6GMMjcxhTSKzFmS6MyQvEkO7m+T91ATtbDXYt9pI8hk=";
  };
in
stdenvNoCC.mkDerivation {
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
    devkitppc
    ninja
    python3Minimal
    wibo
  ];

  configurePhase = ''
    runHook preConfigure
    python3 ./configure.py --wrapper ${wibo}/bin/wibo \
      --dtk ${decomp-toolkit}/bin/dtk \
      --objdiff ${objdiff}/bin/objdiff-cli \
      --binutils ${devkitppc}/bin \
      --sjiswrap ${sjiswrap} \
      --compilers ${mwcc}
    runHook postConfigure
  '';

  enableParallelBuilding = true;

  installPhase = ''
    runHook preInstall
    ninja progress > $out
    runHook postInstall
  '';
}
