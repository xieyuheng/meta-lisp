#!/usr/bin/env bash

set -e

rm -rf self-build

./meta-lisp.meta build-xvm --config self-meta-package.json
