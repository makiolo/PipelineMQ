@echo off
if exist "boostorg_predef" (
	rmdir /s /q boostorg_predef
)
git clone -q https://github.com/boostorg/predef.git boostorg_predef
curl -s https://raw.githubusercontent.com/makiolo/cmaki_scripts/master/setup.cmd -o setup.cmd
curl -s https://raw.githubusercontent.com/makiolo/cmaki_scripts/master/compile.cmd -o compile.cmd
setup.cmd && compile.cmd
