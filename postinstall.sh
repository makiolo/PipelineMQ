#!/bin/bash

export MODE="${MODE:-Debug}"
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

echo -- detecting platform: 
ls $CMAKI_INSTALL
echo $CMAKI_EMULATOR $CMAKI_INSTALL/cmaki_identifier
$CMAKI_EMULATOR $CMAKI_INSTALL/cmaki_identifier
echo -- ok

