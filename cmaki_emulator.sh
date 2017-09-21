#!/bin/bash

# if [ $# -e 0 ]; then
#     echo $0: [ERROR], usage: ./cmaki_emulator.sh <program>
#     exit 1
# fi

export _DIRNAMEPROGRAM=$(dirname "$1")
export DIRPROGRAM="$( cd "$_DIRNAMEPROGRAM" && pwd )"
export BASENAMEPROGRAM=$(basename "$1")
export CMAKI_PWD="${CMAKI_PWD:-$(pwd)}"
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

echo "DIRPROGRAM = $DIRPROGRAM"
echo "CMAKI_PWD = $CMAKI_PWD"
echo "CMAKI_INSTALL = $CMAKI_INSTALL"
echo "CMAKI_EMULATOR = $CMAKI_EMULATOR"
echo "BASENAMEPROGRAM = $BASENAMEPROGRAM"

cd $DIRPROGRAM
if [[ "$WINEARCH" = "win32" ]]; then
	wine ./$BASENAMEPROGRAM.exe "${@:2}"
elif [[ "$WINEARCH" = "win64" ]]; then
	wine ./$BASENAMEPROGRAM.exe "${@:2}"
elif [[ "$ANDROID_NDK_REVISION" = "13b" ]]; then
	unset LD_LIBRARY_PATH
	qemu-arm -L /usr/arm-linux-gnueabi ./$BASENAMEPROGRAM "${@:2}"
elif [[ "$EMSDK" = "/emsdk_portable" ]]; then
	nodejs ./$BASENAMEPROGRAM.js "${@:2}"
else
	echo $CMAKI_EMULATOR $BASENAMEPROGRAM "${@:2}"
	$CMAKI_EMULATOR ./$BASENAMEPROGRAM "${@:2}"
fi
