{
  description = "Sorting Visualizer";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      forAllSystems = nixpkgs.lib.genAttrs systems;
    in
    {
      packages = forAllSystems (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in
        {
          default = pkgs.stdenv.mkDerivation {
            pname = "sorting-visualizer";
            version = "2.0.0-rc.1";

            src = ../.;

            nativeBuildInputs = [
              # Build tools are provided by Nix; wxWidgets and OpenMP below
              # are linked from the native Nix package set.
              pkgs.cmake
              pkgs.ninja
            ];

            buildInputs = [
              pkgs.llvmPackages.openmp
              pkgs.wxGTK32
            ];

            dontConfigure = true;
            dontBuild = true;

            installPhase = ''
              ${../scripts/install.sh} build "$out"
            '';
          };
        });

      devShells = forAllSystems (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in
        {
          default = pkgs.mkShell {
            packages = [
              pkgs.cmake
              pkgs.ninja
              pkgs.gcc
              pkgs.llvm
              pkgs.gdb
              pkgs.wxGTK32
            ];

            buildInputs = [
              pkgs.llvmPackages.openmp
            ];
          };
        });
    };
}
