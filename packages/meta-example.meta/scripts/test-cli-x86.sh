#!/usr/bin/env bash

set -e

x86=./bin/x86
x86_exe=build/main.x86.exe

echo "=== hello ==="
$x86 run $x86_exe -- hello

echo "=== add 1 2 ==="
$x86 run $x86_exe -- add 1 2

echo "=== mul --x 3 --y 4 ==="
$x86 run $x86_exe -- mul --x 3 --y 4

echo "=== bye ==="
$x86 run $x86_exe -- bye

echo "=== passthrough -- foo bar baz ==="
$x86 run $x86_exe -- passthrough -- foo bar baz

echo "=== no command ==="
$x86 run $x86_exe

echo "=== unknown command ==="
$x86 run $x86_exe -- badcmd