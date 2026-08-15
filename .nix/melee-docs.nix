{
  lib,
  stdenvNoCC,
  doxygen,
  python3,
  runCommand,
  wibo,
  mwcc,
}:
let
  mwcc_args = [
    "-nowraplines"
    "-msgstyle" "gcc"
    "-lang" "c"
    "-cwd" "source"
    "-Cpp_exceptions" "off"
    "-proc" "gekko"
    "-DGEKKO"
    "-fp" "hard"
    "-fp_contract" "on"
    "-O4,p"
    "-enum" "int"
    "-nodefaults"
    "-inline" "auto"
    "-requireprotos"
    "-warn" "off"
    "-c"
  ];
in
stdenvNoCC.mkDerivation {
  name = "melee-docs";

  nativeBuildInputs = [
    doxygen
    (python3.withPackages (ps: with ps; [
      pcpp
    ]))
    wibo
  ];

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.unions [
      ../Doxyfile
      ../docs
      ../extern
      ../src
      ../tools/ctx_template.html
      ../tools/doxygen-awesome-css
      ../tools/m2ctx/m2ctx.py
      ../tools/progress-redirect.html
    ];
  };

  buildPhase = ''
    runHook preBuild

    mkdir -p $out
    touch $out/.nojekyll

    mkdir -p build/doxygen
    doxygen Doxyfile
    cp -R build/doxygen/html/* $out

    python tools/m2ctx/m2ctx.py -pqr
    wibo ${mwcc}/GC/1.2.5/mwcceppc.exe ${toString mwcc_args} build/ctx.c -v -o build/ctx.o
    cp build/ctx.html $out/

    # Progress site

    mkdir $out/progress
    cp tools/progress-redirect.html $out/progress/index.html

    runHook postBuild
  '';

  __structuredAttrs = true;
}
