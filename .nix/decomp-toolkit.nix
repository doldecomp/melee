{ lib
, fetchFromGitHub
, git
, rustPlatform
, stdenv
}:

rustPlatform.buildRustPackage rec {
  pname = "decomp-toolkit";
  version = "0.7.4";

  src = fetchFromGitHub {
    owner = "encounter";
    repo = "decomp-toolkit";
    rev = "v${version}";
    hash = "sha256-cpHaoxRr000000000x7Sm+9h0BicrO+jVJA09BBgKJ4=";
  };

  nativeBuildInputs = [
    git
  ];

  cargoLock.lockFile = "${src}/Cargo.lock";
  cargoLock.outputHashes."ar-0.8.0" = "sha256-OLyo+cRRWMsI1i8NsgsBKRJH1XsKW1CculQnJ/wcya0=";
  cargoLock.outputHashes."dol-0.1.0" = "sha256-YfMXWNtmZJhK39R3w98DEGm4y9x59osFGliG36BcuLU=";

  meta = with lib; {
    description = "A GameCube & Wii decompilation toolkit";
    homepage = "https://github.com/encounter/decomp-toolkit";
    license = with licenses; [ asl20 mit ];
    maintainers = with maintainers; [ r-burns ];
    mainProgram = "dtk";
  };
}
