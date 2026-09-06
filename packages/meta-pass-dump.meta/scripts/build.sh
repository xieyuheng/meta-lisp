#!/usr/bin/env bash

set -e

# build by bootstrap compiler

rm -rf build

./meta-lisp.js build-xvm
./meta-lisp.js build-x86

./scripts/sanitize-dump.sh build

# build by self compiler

rm -rf self-build

./meta-lisp.meta build-xvm --config self-meta-package.json

./scripts/sanitize-dump.sh self-build
