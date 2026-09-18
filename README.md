# Sorting Visualizer

![CI](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/ci.yml/badge.svg)
![Release](https://github.com/T-MuangT/sorting-visualizer/actions/workflows/release.yml/badge.svg)
![GitHub Release](https://img.shields.io/github/v/release/T-MuangT/sorting-visualizer)


## How to build and run
1. Run `cmake -B build`.
2. Run `cmake --build build --target package`.
3. The software is compiled in `sorting-visualizer` zipped folder.
4. Extract the software and run.

## How to test the software
1. Run `cmake -B build`.
2. Run `cmake --build build --target tests`.
3. Run `ctest`.