# Sorting Visualizer

![CI/CD](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/ci.yml/badge.svg)
![Nix CI/CD](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/nix.yml/badge.svg)
![Release](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/release.yml/badge.svg)
![GitHub Release](https://img.shields.io/github/v/release/T-MuangT/sorting-visualizer)


## How to build and run with script

The project uses vcpkg manifest mode for wxWidgets. Set `VCPKG_ROOT` to an
installed vcpkg checkout before using the build scripts.

### In POSIX (Bash/Zsh) shell (macOS, Linux)
1. Run `chmod +x ./scripts/install.sh` add permission.
2. Set `VCPKG_ROOT` to the vcpkg checkout (for example, `export VCPKG_ROOT=$HOME/vcpkg`).
3. Run `./scripts/install.sh` to start building.
4. Run `sorting-visualizer` after restarting shell.

### In PowerShell (Windows)
1. Set `VCPKG_ROOT` to the vcpkg checkout (for example, `$env:VCPKG_ROOT = 'C:\vcpkg'`).
2. Run `.\scripts\install.ps1` to start building.
3. Run `sorting-visualizer` after restarting shell.

On Windows, use the Visual Studio Developer PowerShell or ensure the Visual
Studio CMake executable is selected before any MSYS2 CMake executable. Mixing
MSYS2 CMake with the MSVC toolchain can make vcpkg's zlib build fail with
`RC1107`.

If a zlib build has already failed, close CMake/Visual Studio and remove the
failed vcpkg state before retrying:

```powershell
Remove-Item "$env:VCPKG_ROOT\buildtrees\zlib" -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item "$env:VCPKG_ROOT\packages\zlib_x64-windows" -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item ".\vcpkg_installed" -Recurse -Force -ErrorAction SilentlyContinue
.\scripts\install.ps1
```

The repository pins the vcpkg registry in `vcpkg-configuration.json`; this
keeps local and automated dependency versions aligned.

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

## Notes
- In v2.0.0-rc.1, CI/CD pipeline test, Linux build may have failed the graphical tests. However, it has been manually verified that it worked in the environment with display server, therefore, it will be released normally, with the pipeline fix in the future.
- In v2.0.0-rc.2, Due to dependency conflicts, Windows ARM build is temporarily suspended from pipeline.