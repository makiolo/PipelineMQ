#!/bin/bash

# if [ $# -e 0 ]; then
#     echo $0: [ERROR], usage: ./cmaki_emulator.sh <program>
#     exit 1
# fi

export DIRPROGRAM="$( cd "$( dirname "$1" )" && pwd )"
export CMAKI_PWD="${CMAKI_PWD:-$(pwd)"
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

echo "DIRPROGRAM = $DIRPROGRAM"
echo "CMAKI_PWD = $CMAKI_PWD"
echo "CMAKI_INSTALL = $CMAKI_INSTALL"
echo "CMAKI_EMULATOR = $CMAKI_EMULATOR"

if [[ "$WINEARCH" = "win32" ]]; then
	echo cd $DIRPROGRAM and wine $PROGRAM.exe "${@:2}"
	(cd $DIRPROGRAM && wine $PROGRAM.exe "${@:2}")
elif [[ "$WINEARCH" = "win64" ]]; then
	echo cd $DIRPROGRAM and wine $PROGRAM.exe "${@:2}"
	(cd $DIRPROGRAM && wine $PROGRAM.exe "${@:2}")
elif [[ "$ANDROID_NDK_REVISION" = "13b" ]]; then
	unset LD_LIBRARY_PATH
	echo cd $DIRPROGRAM and qemu-arm -L /usr/arm-linux-gnueabi $PROGRAM "${@:2}"
	(cd $DIRPROGRAM && qemu-arm -L /usr/arm-linux-gnueabi $PROGRAM "${@:2}")
elif [[ "$EMSDK" = "/emsdk_portable" ]]; then
	echo cd $DIRPROGRAM and nodejs $PROGRAM.js "${@:2}"
	(cd $DIRPROGRAM && nodejs $PROGRAM.js "${@:2}")
else
	echo cd $DIRPROGRAM and $CMAKI_EMULATOR $PROGRAM "${@:2}"
	(cd $DIRPROGRAM && $CMAKI_EMULATOR $PROGRAM "${@:2}")
fi
