#!/bin/bash

if [ $# -ne 1 ]; then
    echo $0: [ERROR], usage: ./cmaki_emulator.sh <program>
    exit 1
fi

export DIRPROGRAM="$( cd "$( dirname "$1" )" && pwd )"
export CMAKI_PWD="${CMAKI_PWD:-$DIRPROGRAM}/.."
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

if [[ "$WINEARCH" = "win32" ]]; then
	(cd $DIRPROGRAM && wine $PROGRAM.exe)
elif [[ "$WINEARCH" = "win64" ]]; then
	(cd $DIRPROGRAM && wine $PROGRAM.exe)
elif [[ "$ANDROID_NDK_REVISION" = "13b" ]]; then
	unset LD_LIBRARY_PATH
	(cd $DIRPROGRAM && qemu-arm -L /usr/arm-linux-gnueabi $PROGRAM)
elif [[ "$EMSDK" = "/emsdk_portable" ]]; then
	(cd $DIRPROGRAM && nodejs $PROGRAM.js)
else
	(cd $DIRPROGRAM && $CMAKI_EMULATOR $PROGRAM)
fi
