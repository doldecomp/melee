{
  stdenvNoCC,
  lib,
  git,
  rustPlatform,
  src,
}:

rustPlatform.buildRustPackage rec {
  pname = "decomp-toolkit";
  version = src.shortRev;
  inherit src;

  stdenv = stdenvNoCC;

  nativeBuildInputs = [
    git
  ];

  cargoLock.lockFile = "${src}/Cargo.lock";
  cargoLock.allowBuiltinFetchGit = true;

  meta = with lib; {
    description = "A GameCube & Wii decompilation toolkit";
    homepage = "https://github.com/encounter/decomp-toolkit";
    license = with licenses; [
      asl20
      mit
    ];
    maintainers = with maintainers; [ r-burns ];
    mainProgram = "dtk";
  };
}
