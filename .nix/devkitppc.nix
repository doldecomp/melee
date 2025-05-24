{ stdenvNoCC, lib
, buildEnv
, fetchFromGitHub
, fetchpatch
, makeWrapper
, overrideCC
, pkgsCross
}:

let
  version = "46.1";

  tag = "devkitPPC_r${version}";

  ppcCrossBinutils = pkgsCross.ppc-embedded.buildPackages.binutils-unwrapped;

  bintools' = ppcCrossBinutils.overrideAttrs (oa: {
    patches = oa.patches ++ [
      (fetchpatch {
        url = "https://raw.githubusercontent.com/devkitPro/buildscripts/${tag}/dkppc/patches/binutils-${oa.version}.patch";
        hash = "sha256-IOqa20LQYBxfR1KKxkp0hVV21CKd9IZrvNeEyuW09us=";
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
