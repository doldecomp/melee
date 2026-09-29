{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    treefmt-nix.url = "github:numtide/treefmt-nix";
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs =
    {
      self,
      nixpkgs,
      treefmt-nix,
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
            overlays = [ self.overlays.default ];
          };
        in
        {
          packages = {
            default = pkgs.melee;
            melee-docs = pkgs.melee-docs.override {
              rev = self.rev or self.dirtyRev or "unknown";
              lastModifiedDate = self.lastModifiedDate or "";
            };
          };

          formatter =
            (treefmt-nix.lib.evalModule pkgs {
              config = {
                enableDefaultExcludes = true;
                projectRootFile = "flake.nix";
                programs.nixfmt.enable = true;
              };
            }).config.build.wrapper;

          devShells.default = pkgs.mkShellNoCC {
            shellHook = pkgs.melee.postPatch + ''
              export PRE_COMMIT_HOME="$PWD/build/pre-commit"
              mkdir -p "$PRE_COMMIT_HOME"
              ./configure.py ${lib.escapeShellArgs pkgs.melee.configureFlags}
            '';
            inputsFrom = [ pkgs.melee ];
            packages = [
              pkgs.clang-tools-minimal
              pkgs.clang.cc.python
              pkgs.pre-commit
              (pkgs.python3.withPackages (
                ps: with ps; [
                  m2c
                  pcpp
                  pyelftools
                ]
              ))
            ];
          };
        };
    in
    {
      overlays.default = import .nix/overlay.nix;

      packages = lib.genAttrs supportedSystems (s: (perSystem s).packages);
      devShells = lib.genAttrs supportedSystems (s: (perSystem s).devShells);
      formatter = lib.genAttrs supportedSystems (s: (perSystem s).formatter);
    };
}
