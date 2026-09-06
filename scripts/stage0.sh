#!/usr/bin/env bash

set -e

# stage0 -- c runtime vm and loader

# c build

./scripts/run-in.sh std.c build.sh
./scripts/run-in.sh cli.c build.sh
./scripts/run-in.sh xrt.c build.sh
./scripts/run-in.sh xvm.c build.sh
./scripts/run-in.sh x86.c build.sh

# c test

./scripts/run-in.sh std.c test.sh
./scripts/run-in.sh cli.c test.sh
./scripts/run-in.sh xrt.c test.sh
./scripts/run-in.sh xvm.c test.sh
./scripts/run-in.sh x86.c test.sh
