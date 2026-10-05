{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    treefmt-nix.url = "github:numtide/treefmt-nix";
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";

    aurora-src = {
      url = "github:r-burns/aurora/e6a6f02ace4146e8a2f648d5c274dbb7dd89665c";
      flake = false;
    };

    # Tools; configure.py reads their versions from flake.lock
    compilers = {
      url = "https://files.decomp.dev/compilers_20251118.zip";
      flake = false;
    };
    decomp-toolkit = {
      url = "github:encounter/decomp-toolkit/v1.8.3";
      flake = false;
    };
    objdiff = {
      url = "github:encounter/objdiff/v3.8.2";
      flake = false;
    };
    sjiswrap = {
      url = "file+https://github.com/encounter/sjiswrap/releases/download/v1.2.2/sjiswrap-windows-x86.exe";
      flake = false;
    };
    wibo = {
      url = "github:decompals/wibo/0.7.0";
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
    }@inputs:
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
          decomp-toolkit = pkgs.callPackage ./.nix/decomp-toolkit.nix {
            src = inputs.decomp-toolkit;
          };
          mwcc = inputs.compilers;
          objdiff = pkgs.callPackage ./.nix/objdiff.nix { src = inputs.objdiff; };
          wibo = pkgs.pkgsi686Linux.callPackage ./.nix/wibo.nix { src = inputs.wibo; };

          main-dol = pkgsMinPython.requireFile {
            name = "main.dol";
            message = ''
              Add melee's main.dol to your nix store with:
                nix-store --add-fixed sha256 main.dol
            '';
            hash = "sha256-3CFQRRNCQ1C9oXp8ZegjcbRREqXfwenydJqLerDv9kY=";
          };

          # The game's files, for the .dat archives: one hash for the whole
          # directory
          dat-files = pkgsMinPython.requireFile {
            name = "melee-GALE01-files";
            message = ''
              Add melee's extracted files to your nix store with:
                nix store add --name melee-GALE01-files orig/GALE01/files
            '';
            hashMode = "recursive";
            hash = "sha256-S7iM0nxt/3kj9IpuIqD2kcv1rbIbZ7E1gpgJByOo+Vo=";
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
              sjiswrap = inputs.sjiswrap;
              python3 = pkgs.python3.withPackages (ps: [
                ps.pyelftools
                ps.pcpp
              ]);
            };

            default = melee-dtk;

            melee-cmake = pkgsMinPython.pkgsi686Linux.callPackage ./.nix/melee-cmake.nix {
              inherit aurora-src;
            };

            melee-dwarf = pkgs.callPackage ./.nix/melee-cmake.nix {
              inherit aurora-src;
              dwarf = true;
              inherit (pkgs.pkgsCross.ppc-embedded) newlib;
            };

            melee-dat = pkgs.callPackage ./.nix/melee-dat.nix {
              inherit melee-dwarf;
            };

            # The DWARF build with samples of the .dat archives' types
            melee-dat-samples = melee-dwarf.override {
              inherit melee-dat dat-files;
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
              pre-commit install --install-hooks
              ./configure.py ${lib.escapeShellArgs self.packages.${system}.default.configureFlags}
            '';

            inputsFrom = [ self.packages.${system}.default ];

            packages = [
              pkgs.pre-commit
              m2c
              pkgs.cmake
              pkgs.ninja
              pkgs.llvmPackages_22.clang-unwrapped
              pkgs.llvmPackages_22.bintools-unwrapped
              # For tools/dat-cli and the dat CMake preset
              pkgs.cargo
              pkgs.rustc
              pkgs.clippy
              objdiff
            ]
            # The native CMake preset builds 32-bit
            ++ lib.optionals pkgs.stdenv.hostPlatform.isx86_64 [ pkgs.gcc_multi ];

            # Used by the CMake presets
            env = {
              AURORA_SRC = "${aurora-src}";
              NEWLIB_INCLUDE = "${pkgs.pkgsCross.ppc-embedded.newlib}/powerpc-none-eabi/include";
            };
          };
        };
    in
    {
      overlays.default = final: prev: {
        inherit (self.packages.${final.system})
          melee-dtk
          melee-cmake
          melee-dwarf
          melee-dat
          melee-dat-samples
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
