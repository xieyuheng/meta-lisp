#!/usr/bin/env bash

set -e

./scripts/run-in.sh std.js format.sh
./scripts/run-in.sh cli.js format.sh
./scripts/run-in.sh sexp.js format.sh
./scripts/run-in.sh ppml.js format.sh
./scripts/run-in.sh meta-lisp.js format.sh