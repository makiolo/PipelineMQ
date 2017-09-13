#!/bin/bash

export MODE="${MODE:-Debug}"
export CMAKI_INSTALL="${CMAKI_INSTALL:-$CMAKI_PWD/bin}"

echo -- detecting platform: 
$CMAKI_INSTALL/cmaki_identifier
# qemu-arm $CMAKI_INSTALL/cmaki_identifier
echo -- ok

