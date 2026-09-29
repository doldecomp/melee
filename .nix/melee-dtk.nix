{
  stdenvNoCC,
  lib,
  decomp-toolkit,
  devkitppc,
  mwcc,
  objdiff,
  ninja,
  python3,
  wibo,
  main-dol,
  sjiswrap,
}:
stdenvNoCC.mkDerivation (finalAttrs: {
  name = "doldecomp-melee";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions [
      ../config
      ../configure.py
      ../flake.lock
      ../libs
      ../orig/GALE01/sys/.gitkeep
      ../src
      ../tools/download_tool.py
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
    python3
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
