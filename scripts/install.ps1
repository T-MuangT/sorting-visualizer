param(
    [string]$BuildDir = "build",
    [string]$InstallPrefix = "install"
)

$ErrorActionPreference = "Stop"

cmake -S . -B $BuildDir
-G Ninja -DCMAKE_BUILD_TYPE=Release
-DCMAKE_INSTALL_PREFIX="$InstallPrefix"

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

cmake --build $BuildDir --parallel

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

cmake --install $BuildDir

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
