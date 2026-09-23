#!/bin/sh
# Run the CI build locally: src/code.c, src/tests.c, and src/unity.c linked against Dr. Pach's
# public test object, 32-bit x86 on Ubuntu with gcc-multilib. The object is 32-bit x86, which
# the csci232-gcc image cannot link, so this uses an emulated amd64 Ubuntu container. The object
# supplies main() and runs both the instructor_* tests and the eighteen test_* functions in
# src/tests.c. Unity reports PASS or FAIL per test; it does not print the expected value.
#
#   tools/run-tests.sh          # downloads the current tests03.o, builds, runs
#
# For your own tests alone, `make && docker-gcc ./bin/main.exe` is faster (native, no emulation).
set -eu
cd "$(dirname "$0")/.."
num=$(basename "$PWD" | sed -n 's/.*ass\([0-9][0-9]*\).*/\1/p')
[ -n "$num" ] || { echo "cannot read the assignment number from $(basename "$PWD")" >&2; exit 1; }
mkdir -p tests
curl -sSL -o tests/tests.o "https://raw.githubusercontent.com/jpach-cs/232-all-public-tests/main/tests${num}.o"
[ -s tests/tests.o ] || { echo "download of tests${num}.o failed" >&2; exit 1; }
exec docker run --rm --platform linux/amd64 -v "$PWD:/w" -w /w ubuntu:24.04 bash -c '
    set -e
    export DEBIAN_FRONTEND=noninteractive
    # Ubuntu mirrors sometimes serve a stale index mid-sync; retry before giving up, and show why.
    for attempt in 1 2 3; do
        apt-get update -qq >/tmp/apt.log 2>&1 && apt-get install -y -qq gcc-multilib >>/tmp/apt.log 2>&1 && break
        [ "$attempt" = 3 ] && { echo "apt could not install gcc-multilib:" >&2; tail -5 /tmp/apt.log >&2; exit 1; }
        sleep 10
    done
    gcc -Wall -m32 -Isrc -Ilib src/code.c src/tests.c src/unity.c tests/tests.o -o /tmp/run_tests
    /tmp/run_tests'
