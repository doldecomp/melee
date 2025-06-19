{
  sources ? import ./sources.nix,
}:
let
  pkgs = import sources.nixpkgs {
    overlays = [
      (self: super: {
        devkitppc = super.callPackage ./devkitppc.nix {};
        decomp-toolkit = super.callPackage ./decomp-toolkit.nix {};
        mwcc = super.callPackage ./mwcc.nix {};
        objdiff = super.callPackage ./objdiff.nix {};
        wibo = super.pkgsi686Linux.callPackage ./wibo.nix {};

        # Fix gcc-cross compilation
        newlib = super.newlib.overrideAttrs (oa: {
          patches = oa.patches ++ [ ./newlib.patch ];
        });
      })
    ];
  };
in

pkgs.callPackage ./melee.nix {}
