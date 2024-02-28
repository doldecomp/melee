{ lib
, stdenv
, fetchzip
}:
stdenv.mkDerivation {
  name = "GC_WII_COMPILERS";
  src = fetchzip {
    url = "https://files.decomp.dev/compilers_20230715.zip";
    stripRoot = false;
    sha256 = "sha256-IX3byvEUVJB6Rmc+NqO9ZNt1jl95nQpEIqxbHI+uUio=";
  };
  # Patch 1.1 linker to not read garbage from stack.
  # Fixes random crashes under wibo.
  postPatch = ''
    printf '\x51' | dd of=GC/1.1/mwldeppc.exe bs=1 seek=130933 count=1 conv=notrunc
  '';

  installPhase = ''
    runHook preInstall
    cp -r . $out/
    runHook postInstall
  '';
}
