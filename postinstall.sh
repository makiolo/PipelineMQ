#!/bin/bash

export MODE="${MODE:-Debug}"
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

echo -- detecting platform: 
$CMAKI_EMULATOR -h
$CMAKI_EMULATOR $CMAKI_INSTALL/cmaki_identifier.exe
echo -- ok

