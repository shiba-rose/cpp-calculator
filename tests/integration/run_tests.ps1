$testsDir = $PSScriptRoot
$root = Split-Path -Parent (Split-Path -Parent $testsDir)

$exe = Join-Path $root "build\calculator.exe"
$dataDir = Join-Path $testsDir "data"
$inputFile = Join-Path $dataDir "input.txt"
$expectedFile = Join-Path $dataDir "expected.txt"
$resultDir = Join-Path $testsDir "results"

$actualFile = Join-Path $resultDir "actual.txt"
$diffFile = Join-Path $resultDir "diff.txt"

if (!(Test-Path $exe)) {
    Write-Host "ERROR: tests/integration/data/input.txt or expected.txt not found." -ForegroundColor Red
    exit 1
}

if (!(Test-Path $inputFile) -or !(Test-Path $expectedFile)) {
    Write-Host "ERROR: tests/input.txt or tests/expected.txt not found." -ForegroundColor Red
    exit 1
}

New-Item -ItemType Directory -Path $resultDir -Force | Out-Null

$command = '"' + $exe + '" < "' + $inputFile + '"'
$output = @(& cmd.exe /d /c $command 2>&1)
$output | Set-Content -Path $actualFile -Encoding UTF8

$expected = @(
    Get-Content $expectedFile |
    ForEach-Object { $_.Trim() } |
    Where-Object { $_ -ne "" }
)

$actual = @(
    foreach ($line in $output) {
        if ("$line" -match '=\s*(.*?)\s*$') {
            $Matches[1].Trim()
        }
    }
)

$passed = $true
$differences = @()
$count = [Math]::Max($expected.Count, $actual.Count)

for ($i = 0; $i -lt $count; $i++) {
    $e = if ($i -lt $expected.Count) { $expected[$i] } else { "<missing>" }
    $a = if ($i -lt $actual.Count) { $actual[$i] } else { "<missing>" }

    if ($e -ne $a) {
        $passed = $false
        $differences += "Test $($i + 1): expected [$e], actual [$a]"
    }
}

if ($passed) {
    Remove-Item $diffFile -ErrorAction SilentlyContinue
    Write-Host "PASS: all $($expected.Count) tests passed." -ForegroundColor Green
} else {
    $differences | Set-Content -Path $diffFile -Encoding UTF8
    Write-Host "FAIL: $($differences.Count) test(s) failed." -ForegroundColor Red
    Write-Host "See: $diffFile"
    exit 1
}

Write-Host "Full output: $actualFile"
