{ lib
, fetchFromGitHub
, fontconfig
, pkg-config
, rustPlatform
, stdenv
}:

rustPlatform.buildRustPackage rec {
  pname = "objdiff";
  version = "2.7.1";

  src = fetchFromGitHub {
    owner = "encounter";
    repo = "objdiff";
    rev = "v${version}";
    hash = "sha256-KnWStN8X1GmuBs0sUVqiR2To72N8XYNvPJPNvIYQUv4=";
  };

  cargoLock.lockFile = "${src}/Cargo.lock";

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
