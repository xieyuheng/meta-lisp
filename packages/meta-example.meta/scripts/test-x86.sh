#!/usr/bin/env bash

set -e

x86=../x86.c/src/x86.exe
x86_exe=build/test.x86.exe

$x86 run $x86_exe