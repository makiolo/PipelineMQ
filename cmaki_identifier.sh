#!/bin/bash
export DIRSCRIPT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export CC="${CC:-gcc}"
export CXX="${CXX:-g++}"
export MODE="${MODE:-Debug}"
export CMAKI_PWD="${CMAKI_PWD:-$DIRSCRIPT}/.."
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

if [[ "$WINEARCH" = "win32" ]]; then
	wine $CMAKI_INSTALL/cmaki_identifier.exe
elif [[ "$WINEARCH" = "win64" ]]; then
	wine $CMAKI_INSTALL/cmaki_identifier.exe
elif [[ "$ANDROID_NDK_REVISION" = "13b" ]]; then
	unset LD_LIBRARY_PATH
	qemu-arm -L /usr/arm-linux-gnueabi $CMAKI_INSTALL/cmaki_identifier
elif [[ "$EMSDK" = "/emsdk_portable" ]]; then
	(cd $DIRSCRIPT && $CMAKI_EMULATOR $CMAKI_INSTALL/cmaki_identifier.js)
else
	$CMAKI_EMULATOR $CMAKI_INSTALL/cmaki_identifier
fi

