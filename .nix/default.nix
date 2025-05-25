{
  sources ? import ./sources.nix,
}:
let
  pkgs = import sources.nixpkgs {
    overlays = [
      (self: super: {
        decomp-toolkit = super.callPackage ./decomp-toolkit.nix {};
        mwcc = super.callPackage ./mwcc.nix {};
        objdiff = super.callPackage ./objdiff.nix {};
        wibo = super.pkgsi686Linux.callPackage ./wibo.nix {};
      })
    ];
  };
in

pkgs.callPackage ./melee.nix {}
