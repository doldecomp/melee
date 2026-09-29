{
  stdenvNoCC,
  lib,
  fetchpatch,
  makeWrapper,
  pkgsCross,
}:

let
  version = "50";

  tag = "devkitPPC_r${version}";

  ppcCrossBinutils = pkgsCross.ppc-embedded.buildPackages.binutils-unwrapped;

  bintools' = ppcCrossBinutils.overrideAttrs (oa: {
    patches = oa.patches ++ [
      (fetchpatch {
        url = "https://raw.githubusercontent.com/devkitPro/buildscripts/${tag}/patches/binutils-2.46.0-1.patch";
        hash = "sha256-EHXIn7Atkz5dkkRZr68W8u/mXRTJ2Kpb5dlrwM6YSgY=";
      })
    ];
  });
in
stdenvNoCC.mkDerivation {
  pname = "devkitppc";
  inherit version;
  nativeBuildInputs = [
    makeWrapper
  ];

  buildCommand = ''
    for bindir in '${lib.getBin bintools'}/bin'; do
      cd "$bindir"
      for f in powerpc-none-eabi-*; do
        short="$(echo "$f" | sed s/powerpc-none-eabi-/powerpc-eabi-/)"
        makeWrapper "$bindir/$f" "$out/bin/$short"
      done
    done
  '';
}
