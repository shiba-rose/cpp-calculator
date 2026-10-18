param(
    [string]$Executable = ".\build\calculator.exe"
)

$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
$exe = Join-Path $root $Executable
$caseFile = Join-Path $PSScriptRoot "cases.txt"
$resultsDir = Join-Path $PSScriptRoot "results"
$actualFile = Join-Path $resultsDir "actual.txt"
$diffFile = Join-Path $resultsDir "diff.txt"

if (-not (Test-Path $exe)) {
    Write-Error "Calculator executable not found: $exe. Build the project first."
    exit 2
}
if (-not (Test-Path $resultsDir)) {
    New-Item -ItemType Directory -Path $resultsDir | Out-Null
}

$cases = Get-Content $caseFile | Where-Object {
    $_.Trim() -ne "" -and -not $_.Trim().StartsWith("#")
}

$passed = 0
$failed = 0
$details = [System.Collections.Generic.List[string]]::new()
$actualLog = [System.Collections.Generic.List[string]]::new()

foreach ($case in $cases) {
    $parts = $case -split "\|", 2
    $inputLine = $parts[0]
    $expected = @()
    if ($parts.Count -gt 1 -and $parts[1].Trim() -ne "") {
        $expected = $parts[1].Split(",") | ForEach-Object { $_.Trim() }
    }

    # A fresh process isolates the symbol table between test cases.
    $programInput = @($inputLine, "quit")
    $output = $programInput | & $exe 2>&1 | Out-String
    $output = $output -replace "\r", ""
    $found = [regex]::Matches($output, "=\s*(-?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)\s*(?:\n|$)") |
        ForEach-Object { $_.Groups[1].Value }

    $ok = $found.Count -eq $expected.Count
    if ($ok) {
        for ($i = 0; $i -lt $expected.Count; $i++) {
            $expectedNumber = 0.0
            $actualNumber = 0.0
            if (-not [double]::TryParse($expected[$i], [ref]$expectedNumber) -or
                -not [double]::TryParse($found[$i], [ref]$actualNumber) -or
                [Math]::Abs($expectedNumber - $actualNumber) -gt 0.000000001) {
                $ok = $false
                break
            }
        }
    }

    if ($ok) {
        $passed++
        $details.Add("PASS | $inputLine | expected: $($expected -join ', ') | actual: $($found -join ', ')")
    } else {
        $failed++
        $details.Add("FAIL | $inputLine | expected: $($expected -join ', ') | actual: $($found -join ', ')")
        $details.Add("Output: $($output.Trim() -replace "\n", " / ")")
    }
    $actualLog.Add("$inputLine`n$output")
}

$details | Set-Content -Path $diffFile -Encoding utf8
$actualLog | Set-Content -Path $actualFile -Encoding utf8

Write-Host ""
Write-Host "Passed: $passed"
Write-Host "Failed: $failed"
Write-Host "Details: $diffFile"
Write-Host "Full output: $actualFile"

if ($failed -gt 0) {
    exit 1
}
Write-Host "PASS: all $passed tests passed."
exit 0
