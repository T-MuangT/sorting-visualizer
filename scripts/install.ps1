param(
    [string]$BuildDir = "build",
    [string]$InstallPrefix = "install"
)

$ErrorActionPreference = "Stop"

$vcpkgRoot = $env:VCPKG_ROOT
if ([string]::IsNullOrWhiteSpace($vcpkgRoot)) {
    throw "VCPKG_ROOT is not set. Install vcpkg and set VCPKG_ROOT before running this script."
}

$vcpkgCommand = Join-Path $vcpkgRoot "vcpkg.exe"
if (-not (Test-Path $vcpkgCommand)) {
    throw "vcpkg.exe was not found at $vcpkgCommand."
}

# Install the manifest into the build tree used by CMake. This makes the
# wxWidgets runtime DLLs available before configure and keeps the package
# location consistent with VCPKG_INSTALLED_DIR.
New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null
$manifestRoot = (Resolve-Path .).Path
$installRoot = (Join-Path (Resolve-Path $BuildDir).Path "vcpkg_installed")
& $vcpkgCommand install `
    --x-manifest-root="$manifestRoot" `
    --x-install-root="$installRoot" `
    --triplet=x64-windows

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

$cmakeCommand = (Get-Command cmake -ErrorAction Stop).Source
if ($cmakeCommand -match '(?i)\\msys(?:64)?\\') {
    $visualStudioCmake = Get-ChildItem `
        -Path "${env:ProgramFiles}\Microsoft Visual Studio" `
        -Filter cmake.exe `
        -Recurse `
        -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -match '\\Common7\\IDE\\CommonExtensions\\Microsoft\\CMake\\' } |
        Select-Object -First 1

    if ($null -eq $visualStudioCmake) {
        throw "MSYS2 CMake was selected, but no Visual Studio CMake executable was found."
    }

    $cmakeCommand = $visualStudioCmake.FullName
}

& $cmakeCommand -S . -B $BuildDir -G Ninja -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_INSTALL_PREFIX="$InstallPrefix" `
    -DCMAKE_TOOLCHAIN_FILE="$vcpkgRoot\scripts\buildsystems\vcpkg.cmake" `
    -DVCPKG_TARGET_TRIPLET=x64-windows

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

& $cmakeCommand --build $BuildDir --parallel

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

& $cmakeCommand --install $BuildDir

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
