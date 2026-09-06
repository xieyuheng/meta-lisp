#!/usr/bin/env bash

set -e

for asm in $(find lib -name "*.xvm.asm" | sort); do
  exe="${asm%.xvm.asm}.xvm.exe"
  ./bin/meta-lisp.js xvm:assemble "$asm" "$exe"
  ./bin/xvm test "$exe"
done
