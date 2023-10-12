#!/bin/bash
echo "$(sed -n 's/[[:space:]]*MODULE_VERSION("\([^"]*\)");/\1/p' $(dirname $0)/src/xt_WGOBFS_main.c)"
