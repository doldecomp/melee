{
  sources ? import ./sources.nix,
}:
let
  pkgs = import sources.nixpkgs {
    overlays = [
      (self: super: {
        devkitppc = super.callPackage ./devkitppc.nix {};
        mwcc = super.callPackage ./mwcc.nix {};
      })
    ];
  };
in

pkgs.callPackage ./melee.nix {}
