{ lib
, fetchFromGitHub
, fontconfig
, pkg-config
, rustPlatform
, stdenv
, srcOnly
}:

rustPlatform.buildRustPackage rec {
  pname = "objdiff";
  version = "3.0.0";

  src = srcOnly {
    name = "objdiff-patched";
    src = fetchFromGitHub {
      owner = "encounter";
      repo = "objdiff";
      rev = "v${version}";
      hash = "sha256-ycO1koQDRA1WlRmLJrI0xxrIdd+v6IfW+JVAg0cuBa0=";
    };
    patches = [
      ./duplicate-similar-dep.patch
    ];
  };

  cargoBuildFlags = [
    "--workspace" "--exclude objdiff-wasm"
  ];

  cargoTestFlags = cargoBuildFlags;

  cargoLock.lockFile = "${src}/Cargo.lock";
  cargoLock.outputHashes = {
    "gimli-0.32.0" = "sha256-a00uNPu3YbP/z8Xx+MilnAvHMVvDGnDbMqNLmovosQQ=";
    "similar-2.7.0" = "sha256-D25BooCa48IGY7FZQoVW2u8U6BVIcGt7eiwmvT8wsKE=";
  };

  nativeBuildInputs = [
    pkg-config
  ];

  buildInputs = [
    fontconfig
  ];

  meta = with lib; {
    description = "A local diffing tool for decompilation projects";
    homepage = "https://github.com/encounter/objdiff";
    license = with licenses; [ asl20 mit ];
    maintainers = with maintainers; [ r-burns ];
  };
}
