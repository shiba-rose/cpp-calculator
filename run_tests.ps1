
$root = $PSScriptRoot

$exe = Join-Path $root "build\calculator.exe"
$inputFile = Join-Path $root "tests.txt"
$expectedFile = Join-Path $root "expected.txt"
$resultDir = Join-Path $root "test_results"

# Проверяем наличие необходимых файлов
if (!(Test-Path $exe)) {
    Write-Host "ERROR: calculator.exe not found. Build the project first."
    exit 1
}

if (!(Test-Path $inputFile) -or !(Test-Path $expectedFile)) {
    Write-Host "ERROR: tests.txt or expected.txt not found."
    exit 1
}

# Создаём папку для результатов
New-Item -ItemType Directory -Path $resultDir -Force | Out-Null

$actualFile = Join-Path $resultDir "actual.txt"
$diffFile = Join-Path $resultDir "diff.txt"

# Запускаем калькулятор, передавая ему входной файл
$command = '"' + $exe + '" < "' + $inputFile + '"'
$output = @(& cmd.exe /d /c $command 2>&1)

# Сохраняем полный вывод программы
$output | Set-Content -Path $actualFile -Encoding UTF8

# Читаем ожидаемые результаты
$expected = @(
    Get-Content $expectedFile |
    ForEach-Object { $_.Trim() } |
    Where-Object { $_ -ne "" }
)

# Извлекаем результаты после знака =
$actual = @(
    foreach ($line in $output) {
        if ("$line" -match '=\s*(.*?)\s*$') {
            $Matches[1].Trim()
        }
    }
)

# Сравниваем количество результатов и сами значения
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
    Write-Host "Full output: $actualFile"
} else {
    $differences | Set-Content -Path $diffFile -Encoding UTF8
    Write-Host "FAIL: some tests failed." -ForegroundColor Red
    Write-Host "Differences: $diffFile"
    Write-Host "Full output: $actualFile"
    exit 1
}
