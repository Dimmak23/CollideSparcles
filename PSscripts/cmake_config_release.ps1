$directoryPath = "build";

if (-not (Test-Path -Path $directoryPath -PathType Container)) {
    New-Item -ItemType Directory -Path $directoryPath | Out-Null
    Write-Host "Directory created: $directoryPath"
} else {
    Write-Host "Directory already exists: $directoryPath"
};

# Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A "Win64" ; Set-Location ..
# Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A "Win64" ; Set-Location ..  # no such platform
# Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ; Set-Location ..
# Set-Location build ; cmake .. -DCMAKE_C_COMPILER="L:/UCRT_GCC-12-1-0/mingw32/bin/gcc.exe" -DCMAKE_CXX_COMPILER="L:/UCRT_GCC-12-1-0/mingw32/bin/g++.exe" -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ; Set-Location ..
Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja ; Set-Location ..