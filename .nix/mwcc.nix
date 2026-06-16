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
    mkdir -p $out/GC
    cp -r GC/{1.1p1,1.2.5,1.2.5n,1.3.2} $out/GC/
    runHook postInstall
  '';
}
