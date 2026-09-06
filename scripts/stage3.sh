#!/usr/bin/env bash

set -e

# stage3 -- meta-lisp code test

# meta test

./scripts/run-in.sh meta-builtin.meta test.sh
./scripts/run-in.sh meta-math.meta test.sh
./scripts/run-in.sh cli.meta test.sh
./scripts/run-in.sh meta-example.meta test.sh
./scripts/run-in.sh 元语数学 test.sh
./scripts/run-in.sh 命令行 test.sh
./scripts/run-in.sh 元语例子 test.sh
