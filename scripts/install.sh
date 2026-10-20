#!/bin/sh

set -eu

BUILD_DIR="${1:-build}"
INSTALL_PREFIX="${2:-install}"

cmake_path="$(command -v cmake 2>/dev/null || true)"
case "$cmake_path" in
    *[Mm][Ss][Yy][Ss]*)
    echo "MSYS2 CMake cannot configure the MSVC build. Use the Visual Studio CMake executable instead." >&2
    exit 1
    ;;
esac

cmake -S . \
    -B "$BUILD_DIR" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX"

cmake --build "$BUILD_DIR" --parallel

cmake --install "$BUILD_DIR"
