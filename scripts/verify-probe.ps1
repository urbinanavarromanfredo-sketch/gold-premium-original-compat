param(
    [Parameter(Mandatory = $true)]
    [string]$BinaryPath
)
$ErrorActionPreference = 'Stop'
if (-not (Test-Path -LiteralPath $BinaryPath -PathType Leaf)) {
    throw "No existe la DLL esperada: $BinaryPath"
}
$dumpbin = Get-Command dumpbin.exe -ErrorAction Stop
$headers = & $dumpbin.Source /headers $BinaryPath 2>&1 | Out-String
if ($LASTEXITCODE -ne 0) { throw 'dumpbin /headers falló.' }
if ($headers -notmatch '(?i)14C machine \(x86\)') {
    throw 'La salida no identifica la DLL como PE x86 (machine 0x14C).'
}
Write-Host "OK: DLL PE x86 verificada: $BinaryPath"
