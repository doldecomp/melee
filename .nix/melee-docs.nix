{
  lib,
  stdenvNoCC,
  doxygen,
  python3,
  runCommand,
  wibo,
  mwcc,
  # Shown on the cleanup index page; the flake passes its own metadata since
  # the source tree here has no .git to ask.
  rev ? "unknown",
  lastModifiedDate ? "",
}:
let
  generated =
    if lastModifiedDate == "" then
      ""
    else
      "${builtins.substring 0 4 lastModifiedDate}-${builtins.substring 4 2 lastModifiedDate}-${builtins.substring 6 2 lastModifiedDate}";

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
    "-DMUST_MATCH"
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
      ../tools/cleanup-index-template.html
      ../tools/cleanup_index.py
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

    # Cleanup index

    python tools/cleanup_index.py \
      --out $out/cleanup \
      --revision ${lib.escapeShellArg rev} \
      --generated ${lib.escapeShellArg generated}

    runHook postBuild
  '';

  __structuredAttrs = true;
}
