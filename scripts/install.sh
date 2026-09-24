#!/usr/bin/env bash

set -euo pipefail

BUILD_DIR="${1:-build}"
INSTALL_PREFIX="${2:-install}"

cmake -S .
-B "$BUILD_DIR"
-G Ninja
-DCMAKE_BUILD_TYPE=Release
-DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX"

cmake --build "$BUILD_DIR" --parallel

cmake --install "$BUILD_DIR"