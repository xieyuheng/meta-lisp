#!/usr/bin/env bash

set -e

rm -rf snapshot

./bin/meta-lisp.js xvm:test
./scripts/test-cli.sh > scripts/test-cli.sh.out
