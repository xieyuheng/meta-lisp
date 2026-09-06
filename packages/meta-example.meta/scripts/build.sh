#!/usr/bin/env bash

set -e

rm -rf build

./meta-lisp.js build-xvm
./meta-lisp.js build-x86
