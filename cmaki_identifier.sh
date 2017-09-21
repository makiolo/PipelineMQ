#!/bin/bash
export DIRSCRIPT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export CC="${CC:-gcc}"
export CXX="${CXX:-g++}"
export MODE="${MODE:-Debug}"
export CMAKI_PWD="${CMAKI_PWD:-$DIRSCRIPT}/.."
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

$DIRSCRIPT/cmaki_emulator.sh $CMAKI_INSTALL/cmaki_identifier
