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

  ppcCrossGcc      = pkgsCross.ppc-embedded.buildPackages.gcc14.cc;
  ppcCrossBinutils = pkgsCross.ppc-embedded.buildPackages.binutils-unwrapped;

  gcc' = ppcCrossGcc.overrideAttrs (oa: {
    patches = oa.patches ++ [
      (fetchpatch {
        url = "https://raw.githubusercontent.com/devkitPro/buildscripts/${tag}/dkppc/patches/gcc-14.2.0.patch";
        hash = "sha256-b8JY41BUl9NT3QyaXwh/M5OfeqSEQ7WtvPUyHRS4904=";
      })
    ];
  });

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
  #for bindir in '${lib.getBin gcc'}/bin' '${lib.getBin bintools'}/bin'; do
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
