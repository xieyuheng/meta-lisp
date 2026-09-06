#!/usr/bin/env bash

set -e

rm -rf snapshot

./bin/xvm test build/bundle.xvm.exe
