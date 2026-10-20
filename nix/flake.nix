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
              pkgs.cmake
              pkgs.ninja
            ];

            buildInputs = [
              pkgs.llvmPackages.openmp
              pkgs.wxwidgets_3_2
            ];

            # Clang on Darwin needs the OpenMP flag explicitly. The library
            # itself is supplied by llvmPackages.openmp in buildInputs.
            cmakeFlags = pkgs.lib.optionals pkgs.stdenv.hostPlatform.isDarwin [
              "-DOpenMP_CXX_FLAGS=-fopenmp"
              "-DOpenMP_CXX_LIB_NAMES=omp"
              "-DOpenMP_omp_LIBRARY=${pkgs.llvmPackages.openmp}/lib/libomp.dylib"
            ];
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
              pkgs.wxwidgets_3_2
            ];

            buildInputs = [
              pkgs.llvmPackages.openmp
            ];
          };
        });
    };
}
