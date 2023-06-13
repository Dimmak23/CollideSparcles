$directoryPath = "build";

if (-not (Test-Path -Path $directoryPath -PathType Container)) {
    New-Item -ItemType Directory -Path $directoryPath | Out-Null
    Write-Host "Directory created: $directoryPath"
} else {
    Write-Host "Directory already exists: $directoryPath"
};

Set-Location build ; cmake .. -DCMAKE_BUILD_TYPE=Debug -G Ninja ; Set-Location ..