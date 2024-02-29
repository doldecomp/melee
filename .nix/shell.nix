{
  sources ? import ./sources.nix,
}:
let
  pkgs = import sources.nixpkgs {
    overlays = [
      (self: super: {
        decomp-toolkit = super.callPackage ./decomp-toolkit.nix {};
        devkitppc = super.callPackage ./devkitppc.nix {};
        mwcc = super.callPackage ./mwcc.nix {};
        wibo = super.pkgsi686Linux.callPackage ./wibo.nix {};
      })
    ];
  };

  melee = import ./default.nix { inherit sources; };
in

melee.overrideAttrs (oa: {
  nativeBuildInputs = oa.nativeBuildInputs ++ [
    (pkgs.clang-tools.override {
      llvmPackages = pkgs.llvmPackages_15;
    })
    pkgs.clang.cc.python
  ];

  DEVKITPPC = pkgs.devkitppc;

  WINE = "${pkgs.wibo}/bin/wibo";
})
