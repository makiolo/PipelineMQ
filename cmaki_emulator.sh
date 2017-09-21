#!/bin/bash

# if [ $# -e 0 ]; then
#     echo $0: [ERROR], usage: ./cmaki_emulator.sh <program>
#     exit 1
# fi

export _DIRNAMEPROGRAM=$(dirname "$1")
export DIRPROGRAM="$( cd "$_DIRNAMEPROGRAM" && pwd )"
export CMAKI_PWD="${CMAKI_PWD:-$(pwd)}"
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

echo "DIRPROGRAM = $DIRPROGRAM"
echo "CMAKI_PWD = $CMAKI_PWD"
echo "CMAKI_INSTALL = $CMAKI_INSTALL"
echo "CMAKI_EMULATOR = $CMAKI_EMULATOR"

shift
if [[ "$WINEARCH" = "win32" ]]; then
	wine $PROGRAM.exe "$@"
elif [[ "$WINEARCH" = "win64" ]]; then
	wine $PROGRAM.exe "$@"
elif [[ "$ANDROID_NDK_REVISION" = "13b" ]]; then
	unset LD_LIBRARY_PATH
	qemu-arm -L /usr/arm-linux-gnueabi $PROGRAM "$@"
elif [[ "$EMSDK" = "/emsdk_portable" ]]; then
	nodejs $PROGRAM.js "$@"
else
	echo $CMAKI_EMULATOR $PROGRAM "$@"
	$CMAKI_EMULATOR $PROGRAM "$@"
fi
