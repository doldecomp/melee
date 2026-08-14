{
  lib,
  stdenvNoCC,
  decomp-toolkit,
  devkitppc,
  fetchurl,
  mwcc,
  objdiff,
  ninja,
  python3Minimal,
  wibo,
  main-dol,
}:
let
  sjiswrap = fetchurl {
    url = "https://github.com/encounter/sjiswrap/releases/download/v1.2.1/sjiswrap-windows-x86.exe";
    hash = "sha256-6GMMjcxhTSKzFmS6MyQvEkO7m+T91ATtbDXYt9pI8hk=";
  };
in
stdenvNoCC.mkDerivation (finalAttrs: {
  name = "doldecomp-melee";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions [
      ../compile_flags.txt
      ../config
      ../configure.py
      ../extern
      ../orig/GALE01/sys/.gitkeep
      ../src
      ../tools/ninja_syntax.py
      ../tools/project.py
      ../tools/transform_dep.py
    ];
  };

  postPatch = ''
    ln -sfT ${mwcc}/GC tools/mwcc_compiler
    ln -sfT ${main-dol} orig/GALE01/sys/main.dol
  '';

  nativeBuildInputs = [
    decomp-toolkit
    devkitppc
    ninja
    python3Minimal
    wibo
  ];

  configurePhase = ''
    runHook preConfigure
    python3 ./configure.py ${toString finalAttrs.configureFlags}
    runHook postConfigure
  '';

  configureFlags = [
    "--wrapper=wibo"
    "--dtk=${decomp-toolkit}/bin/dtk"
    "--objdiff=${objdiff}/bin/objdiff-cli"
    "--binutils=${devkitppc}/bin"
    "--sjiswrap=${sjiswrap}"
    "--compilers=${mwcc}"
  ];

  installPhase = ''
    runHook preInstall
    cp build/GALE01/report.json $out
    runHook postInstall
  '';

  strictDeps = true;
  __structuredAttrs = true;
})
