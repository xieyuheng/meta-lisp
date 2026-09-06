#!/usr/bin/env bash

set -e

./scripts/run-in.sh std.js clean.sh test.sh
./scripts/run-in.sh cli.js clean.sh test.sh
./scripts/run-in.sh sexp.js clean.sh test.sh
./scripts/run-in.sh ppml.js clean.sh test.sh

./scripts/run-in.sh std.c test.sh
./scripts/run-in.sh cli.c test.sh
./scripts/run-in.sh xrt.c test.sh
./scripts/run-in.sh xvm.c test.sh
./scripts/run-in.sh x86.c test.sh

# meta-lisp.js 的测试驱动 x86.c 产物，须排在 C 之后
./scripts/run-in.sh meta-lisp.js clean.sh test.sh

./scripts/run-in.sh meta-builtin.meta clean.sh test.sh
./scripts/run-in.sh meta-math.meta clean.sh test.sh
./scripts/run-in.sh cli.meta clean.sh test.sh
./scripts/run-in.sh 命令行 clean.sh test.sh
./scripts/run-in.sh 元语数学 clean.sh test.sh
./scripts/run-in.sh 元语例子 clean.sh test.sh
./scripts/run-in.sh meta-example.meta clean.sh test.sh
./scripts/run-in.sh meta-error.meta clean.sh test.sh
./scripts/run-in.sh meta-lisp.meta clean.sh test.sh
./scripts/run-in.sh meta-pass-dump.meta clean.sh test.sh

./scripts/run-in.sh meta-lisp.meta self-test.sh