#!/usr/bin/env bash

set -e

rm -rf self-build

./meta-lisp.meta build --config self-meta-package.json
