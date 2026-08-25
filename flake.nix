{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    treefmt-nix.url = "github:numtide/treefmt-nix";
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs =
    { nixpkgs, treefmt-nix, ... }:

    let
      inherit (nixpkgs) lib;

      outputsFor = output: lib.genAttrs lib.systems.flakeExposed (system: (simpleFlake system).${output});
      outputs = lib.genAttrs (lib.attrNames (simpleFlake "")) outputsFor // {
        overlays.default = import .nix/overlay.nix;
      };

      simpleFlake = system: rec {

        legacyPackages = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
          overlays = [ outputs.overlays.default ];
        };

        packages.default = legacyPackages.melee;

        formatter =
          (treefmt-nix.lib.evalModule legacyPackages {
            config = {
              enableDefaultExcludes = true;
              projectRootFile = "flake.nix";
              programs.nixfmt.enable = true;
            };
          }).config.build.wrapper;

        devShells.default = legacyPackages.mkShellNoCC {
          shellHook = packages.default.postPatch + ''
            ./configure.py ${toString packages.default.configureFlags}
          '';
          packages = packages.default.nativeBuildInputs ++ [
            legacyPackages.clang-tools-minimal
            legacyPackages.clang.cc.python
            (legacyPackages.python3.withPackages (ps: with ps; [ m2c pcpp pyelftools ]))
          ];
        };
      };
    in
    outputs;
}
