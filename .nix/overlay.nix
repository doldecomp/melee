final: prev: {
  devkitppc = final.callPackage ./devkitppc.nix { };
  decomp-toolkit = final.callPackage ./decomp-toolkit.nix { };
  mwcc = final.callPackage ./mwcc.nix { };
  objdiff = final.callPackage ./objdiff.nix { };
  wibo = final.pkgsi686Linux.callPackage ./wibo.nix { };
  melee = final.callPackage ./melee.nix { };

  pythonPackagesExtensions = prev.pythonPackagesExtensions ++ [
    (final: prev: {
      m2c = final.callPackage ./m2c.nix { };
    })
  ];

  clang-tools-minimal = final.runCommand "clang-tools-minimal" { } ''
    mkdir -p $out/bin/
    cp ${final.clang.cc}/bin/clang-format $out/bin/
    cp ${final.clang.cc}/bin/clang-tidy $out/bin/
  '';

  main-dol = final.requireFile {
    name = "main.dol";
    message = ''
      Add melee's main.dol to your nix store with
        nix-store --add-fixed sha256 main.dol
    '';
    hash = "sha256-3CFQRRNCQ1C9oXp8ZegjcbRREqXfwenydJqLerDv9kY=";
  };

  melee-docs = final.callPackage ./melee-docs.nix { };

  melee-gcc-native = final.pkgsi686Linux.callPackage ./melee-gcc-native.nix { };

  aurora-src = final.fetchFromGitHub {
    owner = "r-burns";
    repo = "aurora";
    rev = "e6a6f02ace4146e8a2f648d5c274dbb7dd89665c";
    hash = "sha256-jvnfdnRF5HtZ792lwUs0WYASwG/dHIkp9JaisLdntUc=";
  };

  default = final.melee;
}
