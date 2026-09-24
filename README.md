# Sorting Visualizer

![CI/CD](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/ci.yml/badge.svg)
![Nix CI/CD](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/nix.yml/badge.svg)
![Release](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/release.yml/badge.svg)
![GitHub Release](https://img.shields.io/github/v/release/T-MuangT/sorting-visualizer)


## How to build and run with script

### In POSIX (Bash/Zsh) shell (macOS, Linux)
1. Run `chmod +x ./scripts/install.sh` add permission.
2. Run `./scripts/install.sh` to start building.
3. Run `sorting-visualizer` after restarting shell.

### In PowerShell (Windows)
1. Run `.\scripts\install.ps1` to start building.
2. Run `sorting-visualizer` after restarting shell.

## How to build and run in systems with Nix store
1. Run `nix build ./nix`. The configuration and building will start.
2. Run `nix profile install ./nix` to install `sorting-visualizer` into Nix profile.
3. Run `sorting-visualizer`.

## How to build and run manually
1. Run `cmake -B build` to add configuration and `build` directory.
2. Run `cmake --build build --target package` to build.
3. Extract the software in zipped file inside `build`.
4. Run `sorting-visualizer`.

## How to test the software
1. Run `cmake -B build`.
2. Run `cmake --build build --target tests`.
3. Run `ctest`.