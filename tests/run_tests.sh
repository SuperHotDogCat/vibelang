#!/bin/bash
set -e

# Build compiler
make

echo "Running tests..."

for test_file in tests/*.nov; do
    echo -n "Running $test_file... "
    ./novusc "$test_file" > /dev/null 2>&1
    ll_file="${test_file%.nov}.ll"
    obj_file="${test_file%.nov}.o"
    exe_file="${test_file%.nov}.exe"

    if [ ! -f "$ll_file" ]; then
        echo "FAILED (Compilation)"
        exit 1
    fi

    llc-18 "$ll_file" -relocation-model=pic -filetype=obj -o "$obj_file"

    # Check if there is a wrapper.c
    if [ -f "tests/wrapper.c" ] && [ "$test_file" == "tests/test_interop.nov" ]; then
        gcc "tests/wrapper.c" "$obj_file" -o "$exe_file"
    else
        gcc "$obj_file" -o "$exe_file"
    fi

    set +e
    ./"$exe_file" > /dev/null 2>&1
    exit_code=$?
    set -e

    if [ $exit_code -eq 0 ]; then
        echo "PASSED"
    else
        echo "FAILED (Exit code $exit_code)"
        exit 1
    fi

    # Cleanup
    rm -f "$ll_file" "$obj_file" "$exe_file"
done

echo "All tests passed!"
