{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    treefmt-nix.url = "github:numtide/treefmt-nix";
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";

    aurora-src = {
      url = "github:r-burns/aurora/e6a6f02ace4146e8a2f648d5c274dbb7dd89665c";
      flake = false;
    };
  };

  outputs =
    {
      self,
      nixpkgs,
      treefmt-nix,
      aurora-src,
      ...
    }:
    let
      inherit (nixpkgs) lib;

      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
      ];

      perSystem =
        system:
        let
          pkgs = import nixpkgs {
            inherit system;
            config.allowUnfree = true;
          };

          pkgsMinPython = pkgs.appendOverlays [
            (final: prev: {
              python3 = prev.python3Minimal;
            })
          ];

          devkitppc = pkgsMinPython.callPackage ./.nix/devkitppc.nix { };
          decomp-toolkit = pkgs.callPackage ./.nix/decomp-toolkit.nix { };
          mwcc = pkgsMinPython.callPackage ./.nix/mwcc.nix { };
          objdiff = pkgs.callPackage ./.nix/objdiff.nix { };
          wibo = pkgs.pkgsi686Linux.callPackage ./.nix/wibo.nix { };

          main-dol = pkgsMinPython.requireFile {
            name = "main.dol";
            message = ''
              Add melee's main.dol to your nix store with:
                nix-store --add-fixed sha256 main.dol
            '';
            hash = "sha256-3CFQRRNCQ1C9oXp8ZegjcbRREqXfwenydJqLerDv9kY=";
          };

          m2c = pkgs.python3Packages.callPackage ./.nix/m2c.nix { };

        in
        {
          packages = rec {
            melee-dtk = pkgs.callPackage ./.nix/melee-dtk.nix {
              inherit
                decomp-toolkit
                devkitppc
                mwcc
                objdiff
                wibo
                main-dol
                ;
              python3 = pkgs.python3.withPackages (ps: [
                ps.pyelftools
                ps.pcpp
              ]);
            };

            default = melee-dtk;

            melee-cmake = pkgsMinPython.pkgsi686Linux.callPackage ./.nix/melee-cmake.nix {
              inherit aurora-src;
            };

            melee-docs =
              (pkgs.callPackage ./.nix/melee-docs.nix {
                inherit mwcc;
              }).override
                {
                  rev = self.rev or self.dirtyRev or "unknown";
                  lastModifiedDate = self.lastModifiedDate or "";
                };
          };

          formatter =
            (treefmt-nix.lib.evalModule pkgsMinPython {
              config = {
                enableDefaultExcludes = true;
                projectRootFile = "flake.nix";
                programs.nixfmt.enable = true;
              };
            }).config.build.wrapper;

          devShells.default = pkgs.mkShellNoCC {
            shellHook = self.packages.${system}.default.postPatch + ''
              export PRE_COMMIT_HOME="$PWD/build/pre-commit"
              mkdir -p "$PRE_COMMIT_HOME"
              ./configure.py ${lib.escapeShellArgs self.packages.${system}.default.configureFlags}
            '';

            inputsFrom = [ self.packages.${system}.default ];

            packages = [
              pkgs.pre-commit
              m2c
            ];
          };
        };
    in
    {
      overlays.default = final: prev: {
        inherit (self.packages.${final.system})
          melee-dtk
          melee-cmake
          melee-docs
          m2c
          ;
        default = self.packages.${final.system}.default;
      };

      packages = lib.genAttrs supportedSystems (s: (perSystem s).packages);
      devShells = lib.genAttrs supportedSystems (s: (perSystem s).devShells);
      formatter = lib.genAttrs supportedSystems (s: (perSystem s).formatter);
    };
}
