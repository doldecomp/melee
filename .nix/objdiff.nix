{
  lib,
  fontconfig,
  pkg-config,
  rustPlatform,
  src,
}:

rustPlatform.buildRustPackage (finalAttrs: {
  pname = "objdiff";
  version = src.shortRev;

  inherit src;

  cargoBuildFlags = [
    "--workspace"
    "--exclude objdiff-wasm"
    "--bin objdiff-cli"
  ];

  cargoTestFlags = finalAttrs.cargoBuildFlags;

  cargoLock.lockFile = "${finalAttrs.src}/Cargo.lock";
  cargoLock.allowBuiltinFetchGit = true;

  nativeBuildInputs = [
    pkg-config
  ];

  buildInputs = [
    fontconfig
  ];

  meta = with lib; {
    description = "A local diffing tool for decompilation projects";
    homepage = "https://github.com/encounter/objdiff";
    license = with licenses; [
      asl20
      mit
    ];
    maintainers = with maintainers; [ r-burns ];
  };
})
