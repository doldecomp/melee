{
  lib,
  rustPlatform,
  melee-dwarf,
}:

rustPlatform.buildRustPackage {
  pname = "melee-dat";
  version = "0.1.0";

  src = lib.cleanSource ../.;

  cargoBuildFlags = [
    "-p"
    "melee-dat"
  ];
  cargoTestFlags = [
    "-p"
    "melee-dat"
  ];

  cargoLock.lockFile = ../Cargo.lock;

  # Type information for introspecting the archives
  env.MELEE_DWARF_ELF = "${melee-dwarf}/melee.elf";

  preBuild = ''
    export CARGO_TARGET_DIR="$PWD/target"
  '';

  meta = {
    description = "Tooling for introspecting and matching Melee's DAT archives";
    mainProgram = "melee-dat";
  };
}
