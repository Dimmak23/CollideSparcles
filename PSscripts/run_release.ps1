# $filePath = ".\executables\RELEASE\managingThreads\managingThreads.exe";

# if (-not (Test-Path -Path ".\$filePath" -PathType Leaf)) {
#     Write-Host "There is no such file: '$filePath'";
# } else {
#     Start-Process -FilePath $filePath;
#     $filePath;
# };

.\executables\RELEASE\sparcle\sparcle.exe
