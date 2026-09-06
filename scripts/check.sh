#!/usr/bin/env bash

set -e

./scripts/run-in.sh std.js check.sh
./scripts/run-in.sh cli.js check.sh
./scripts/run-in.sh sexp.js check.sh
./scripts/run-in.sh ppml.js check.sh
./scripts/run-in.sh meta-lisp.js check.sh