#!/usr/bin/env bash

set -e

rm -rf snapshot

./bin/meta-lisp.js xvm:test
