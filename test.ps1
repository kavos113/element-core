$bin_dir = '.\cmake-build-debug\bin'

echo "Searching for executables in $bin_dir..."
Get-ChildItem -Recurse -Filter '*.exe*' -Path $bin_dir | ForEach-Object {
    Write-Host "Running $($_.FullName)..."
    & $_.FullName
}