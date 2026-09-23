#!/bin/sh
# VS Code starts the debugger from an arbitrary working directory, sometimes ~/.bin itself,
# which puts the docker-gcc shim outside the Montana Tech scope it guards. Enter this repo
# first, then hand off to the shim so gdb runs in the GCC 9.2.0 container.
cd "$(dirname "$0")/.." && exec "$HOME/.bin/gdb" "$@"
