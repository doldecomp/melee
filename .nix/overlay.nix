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

  clang-format-minimal = final.runCommand "clang-format-minimal" {} ''
    mkdir -p $out/bin/
    cp ${final.clang.cc}/bin/clang-format $out/bin/
  '';

  main-dol = final.requireFile {
    name = "main.dol";
    message = ''
      Add melee's main.dol to your nix store with
        nix-store --add-fixed sha256 main.dol
    '';
    hash = "sha256-3CFQRRNCQ1C9oXp8ZegjcbRREqXfwenydJqLerDv9kY=";
  };

  default = final.melee;
}
