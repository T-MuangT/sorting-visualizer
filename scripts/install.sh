#!/bin/sh

set -eu

BUILD_DIR="${1:-build}"
INSTALL_PREFIX="${2:-install}"

: "${VCPKG_ROOT:?VCPKG_ROOT must point to a vcpkg installation}"

vcpkg_command="$VCPKG_ROOT/vcpkg.exe"
if [ ! -x "$vcpkg_command" ]; then
    echo "vcpkg executable was not found at $vcpkg_command" >&2
    exit 1
fi

# Install the manifest into the build tree used by CMake so wxWidgets' runtime
# DLLs are present before configure and at the path expected by the project.
mkdir -p "$BUILD_DIR"
"$vcpkg_command" install \
    --x-manifest-root="$(pwd)" \
    --x-install-root="$BUILD_DIR/vcpkg_installed" \
    --triplet=x64-windows

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
    -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build "$BUILD_DIR" --parallel

cmake --install "$BUILD_DIR"