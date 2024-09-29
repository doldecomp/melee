{ lib
, fetchFromGitHub
, git
, rustPlatform
, stdenv
}:

rustPlatform.buildRustPackage rec {
  pname = "decomp-toolkit";
  version = "1.0.0";

  src = fetchFromGitHub {
    owner = "encounter";
    repo = "decomp-toolkit";
    rev = "v${version}";
    hash = "sha256-4fRdN5m9eyASFfyWTytQFu8mjENXhnuwlFvQFNjcdiE=";
  };

  nativeBuildInputs = [
    git
  ];

  cargoLock.lockFile = "${src}/Cargo.lock";
  cargoLock.outputHashes."ar-0.8.0" = "sha256-OLyo+cRRWMsI1i8NsgsBKRJH1XsKW1CculQnJ/wcya0=";

  meta = with lib; {
    description = "A GameCube & Wii decompilation toolkit";
    homepage = "https://github.com/encounter/decomp-toolkit";
    license = with licenses; [ asl20 mit ];
    maintainers = with maintainers; [ r-burns ];
    mainProgram = "dtk";
  };
}
