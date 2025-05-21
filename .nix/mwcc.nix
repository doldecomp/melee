{ lib
, stdenv
, fetchzip
}:
stdenv.mkDerivation {
  name = "GC_WII_COMPILERS";
  src = fetchzip {
    url = "https://files.decomp.dev/compilers_20250520.zip";
    stripRoot = false;
    sha256 = "sha256-+j3bLERQ6CFkqRUaQN6Q8QIE+NMJcNZcQM8b2wvE7RQ=";
  };

  installPhase = ''
    runHook preInstall
    cp -r . $out/
    runHook postInstall
  '';
}
