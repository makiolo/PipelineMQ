#!/bin/bash

export MODE="${MODE:-Debug}"
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"
export CMAKI_EMULATOR="${CMAKI_EMULATOR:-}"

echo -- detecting platform: 
$CMAKI_PWD/node_modules/cmaki/ci/detect_operative_system.sh
echo -- ok

