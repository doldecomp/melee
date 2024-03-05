{ lib
, fetchFromGitHub
, git
, rustPlatform
, stdenv
}:

rustPlatform.buildRustPackage rec {
  pname = "decomp-toolkit";
  version = "0.7.5";

  src = fetchFromGitHub {
    owner = "encounter";
    repo = "decomp-toolkit";
    rev = "v${version}";
    hash = "sha256-DvZCJRGn6C2FXVlMQTUdmT5+J8raM+RE2Jhzx08VhT4=";
  };

  nativeBuildInputs = [
    git
  ];

  cargoLock.lockFile = "${src}/Cargo.lock";
  cargoLock.outputHashes."ar-0.8.0" = "sha256-OLyo+cRRWMsI1i8NsgsBKRJH1XsKW1CculQnJ/wcya0=";
  cargoLock.outputHashes."dol-0.1.0" = "sha256-YfMXWNtmZJhK39R3w98DEGm4y9x59osFGliG36BcuLU=";
  cargoLock.outputHashes."objdiff-core-1.0.0" = "sha256-KXQ8oTRhe7zsmQH69dz4/qgiwcLfEBjTbSi5IJHlL08=";

  meta = with lib; {
    description = "A GameCube & Wii decompilation toolkit";
    homepage = "https://github.com/encounter/decomp-toolkit";
    license = with licenses; [ asl20 mit ];
    maintainers = with maintainers; [ r-burns ];
    mainProgram = "dtk";
  };
}
