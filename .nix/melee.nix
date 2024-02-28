{ lib
, stdenv
, decomp-toolkit
, devkitppc
, fetchurl
, mwcc
, ninja
, python3
, wibo
}:
let
  sjiswrap = fetchurl {
    url = "https://github.com/encounter/sjiswrap/releases/download/v1.1.1/sjiswrap-windows-x86.exe";
    hash = "sha256-J6PF1PJj5OuW5WGc/Noi9F0zzNEhEEx/9qN+FbP0J80=";
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

  shellHook = ''
    runHook postPatch
  '';

  nativeBuildInputs = [
    decomp-toolkit
    devkitppc
    ninja
    python3
    wibo
  ];

  configurePhase = ''
    runHook preConfigure
    python3 ./configure.py --wrapper ${wibo}/bin/wibo \
      --build-dtk ${decomp-toolkit}/bin/dtk \
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
