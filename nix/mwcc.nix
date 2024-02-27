{ lib
, stdenv
, fetchzip
}:
stdenv.mkDerivation {
  name = "GC_WII_COMPILERS";
  src = fetchzip {
    url = "https://cdn.discordapp.com/attachments/727918646525165659/1129759991696457728/GC_WII_COMPILERS.zip";
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
