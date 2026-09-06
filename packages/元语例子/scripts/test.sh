#!/usr/bin/env bash

set -e

rm -rf snapshot

./meta-lisp.js test-xvm
./scripts/test-cli.sh > scripts/test-cli.sh.out
