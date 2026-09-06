#!/usr/bin/env bash

set -e

# stage2 -- meta-lisp code build

# meta build

./scripts/run-in.sh meta-builtin.meta build.sh
./scripts/run-in.sh meta-math.meta build.sh
./scripts/run-in.sh cli.meta build.sh
./scripts/run-in.sh meta-example.meta build.sh
./scripts/run-in.sh 元语数学 build.sh
./scripts/run-in.sh 命令行 build.sh
./scripts/run-in.sh 元语例子 build.sh
