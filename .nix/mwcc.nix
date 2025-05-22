{ lib
, stdenv
, fetchzip
}:
stdenv.mkDerivation {
  name = "GC_WII_COMPILERS";
  src = fetchzip {
    url = "https://files.decomp.dev/compilers_20250520.zip";
    stripRoot = false;
    sha256 = "sha256-1HzbrLweTt3BdiD75y5Lcd0Hcf+IgH3puRYETLMqbpg=";
  };

  installPhase = ''
    runHook preInstall
    cp -r . $out/
    runHook postInstall
  '';
}
