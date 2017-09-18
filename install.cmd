@echo off
if exist "boostorg_predef" (
	rmdir /s /q boostorg_predef
)

git clone -q https://github.com/boostorg/predef.git boostorg_predef

:: powershell -c "$source = 'https://raw.githubusercontent.com/makiolo/cmaki_scripts/master/setup.cmd'; $dest = $env:TEMP + '\bootstrap.cmd'; $WebClient = New-Object System.Net.WebClient; $WebClient.DownloadFile($source,$dest); Invoke-Expression $dest"
:: powershell -c "$source = 'https://raw.githubusercontent.com/makiolo/cmaki_scripts/master/compile.cmd'; $dest = $env:TEMP + '\bootstrap.cmd'; $WebClient = New-Object System.Net.WebClient; $WebClient.DownloadFile($source,$dest); Invoke-Expression $dest"

curl -s https://raw.githubusercontent.com/makiolo/cmaki_scripts/master/setup.cmd > __setup.cmd
curl -s https://raw.githubusercontent.com/makiolo/cmaki_scripts/master/compile.cmd > __compile.md
call __setup.cmd && call __compile.cmd
del __setup.cmd
del __compile.cmd
