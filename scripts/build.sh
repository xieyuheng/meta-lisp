#!/usr/bin/env bash

set -e

./scripts/run-in.sh std.c clean.sh build.sh
./scripts/run-in.sh cli.c clean.sh build.sh
./scripts/run-in.sh xrt.c clean.sh build.sh
./scripts/run-in.sh xvm.c clean.sh build.sh
./scripts/run-in.sh x86.c clean.sh build.sh