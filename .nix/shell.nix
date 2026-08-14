{
  sources ? import ./sources.nix,
}:
let
  pkgs = import sources.nixpkgs {
    overlays = [
      (self: super: {
        decomp-toolkit = super.callPackage ./decomp-toolkit.nix { };
        mwcc = super.callPackage ./mwcc.nix { };
        wibo = super.pkgsi686Linux.callPackage ./wibo.nix { };
      })
    ];
  };

  melee = import ./default.nix { inherit sources; };
in

melee.overrideAttrs (oa: {
  nativeBuildInputs = oa.nativeBuildInputs ++ [
    pkgs.clang-tools
    pkgs.clang.cc.python
    (pkgs.python3.withPackages (ps: [
      m2c
      pyelftools
      pcpp
    ]))
  ];

  WINE = "${pkgs.wibo}/bin/wibo";
})
