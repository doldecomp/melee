{ lib
, fetchFromGitHub
, git
, rustPlatform
, stdenv
}:

rustPlatform.buildRustPackage rec {
  pname = "decomp-toolkit";
  version = "0.9.6";

  src = fetchFromGitHub {
    owner = "encounter";
    repo = "decomp-toolkit";
    rev = "v${version}";
    hash = "sha256-mgdohsZ0ZkTSg/UsGVBPmtlJFa1rKMG6aa4XG1S9F4Y=";
  };

  nativeBuildInputs = [
    git
  ];

  cargoLock.lockFile = "${src}/Cargo.lock";
  cargoLock.outputHashes."ar-0.8.0" = "sha256-OLyo+cRRWMsI1i8NsgsBKRJH1XsKW1CculQnJ/wcya0=";
  cargoLock.outputHashes."objdiff-core-2.0.0-alpha.3" = "sha256-E597zRlSpxrTGino7jqoQmyxWkLYXT1P6U2PRolm0Ek=";
  cargoLock.outputHashes."ppc750cl-0.3.0" = "sha256-nMJk+rgu7Ydi2VZfodJk0kBz9xLLVBVz0vEZPee8Q6M=";

  meta = with lib; {
    description = "A GameCube & Wii decompilation toolkit";
    homepage = "https://github.com/encounter/decomp-toolkit";
    license = with licenses; [ asl20 mit ];
    maintainers = with maintainers; [ r-burns ];
    mainProgram = "dtk";
  };
}
