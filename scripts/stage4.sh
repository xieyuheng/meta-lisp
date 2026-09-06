#!/usr/bin/env bash

set -e

# stage4 -- meta-lisp compiler

# self compiler by bootstrap compiler

./scripts/run-in.sh meta-lisp.meta build.sh
./scripts/run-in.sh meta-lisp.meta test.sh

# pass dump test

./scripts/run-in.sh meta-pass-dump.meta build.sh
./scripts/run-in.sh meta-pass-dump.meta test.sh

# self compiler by self compiler

./scripts/run-in.sh meta-lisp.meta self-build.sh
# ./scripts/run-in.sh meta-lisp.meta self-test.sh
