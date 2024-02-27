{ lib
, stdenv
, devkitppc
, mwcc
, python3
, wibo
}:
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
    devkitppc
    python3
    wibo
  ];

  preBuild = ''
    export HOME="$(mktemp -d)"
  '';

  DEVKITPPC = devkitppc;

  WINE = "${wibo}/bin/wibo";

  enableParallelBuilding = true;

  installPhase = ''
    runHook preInstall
    mkdir -p $out
    cp build/ssbm.us.1.2/main.dol $out/
    runHook postInstall
  '';
}
