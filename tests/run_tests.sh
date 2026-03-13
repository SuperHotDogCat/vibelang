#!/bin/bash

# Configuration
NOVUSC="./novusc"
LLC="llc-18"
GCC="gcc"
STD_LIB_DIR="./lib"
export NOVUS_PATH=$STD_LIB_DIR

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Ensure compiler is built
if [ ! -f "$NOVUSC" ]; then
    echo "Compiler not found. Building..."
    make
fi

PASSED=0
FAILED=0
FAILED_TESTS=""

echo "Running Novus Test Suite..."
echo "---------------------------"

for test_file in tests/*.nov; do
    # Skip test_interop.nov as it requires a special build process with wrapper.c
    if [[ "$test_file" == "tests/test_interop.nov" ]]; then
        continue
    fi

    base_name=$(basename "$test_file" .nov)
    ll_file="tests/${base_name}.ll"
    o_file="tests/${base_name}.o"
    exe_file="tests/${base_name}_exe"

    echo -n "Testing $test_file... "

    # Compile to LLVM IR
    $NOVUSC "$test_file" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}FAILED (Compilation)${NC}"
        FAILED=$((FAILED + 1))
        FAILED_TESTS="$FAILED_TESTS\n$test_file (Compilation)"
        continue
    fi

    # Check if .ll file was generated in the current directory or tests/
    if [ -f "${base_name}.ll" ]; then
        mv "${base_name}.ll" "$ll_file"
    fi

    # Compile to Object file
    $LLC "$ll_file" -relocation-model=pic -filetype=obj -o "$o_file" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}FAILED (LLC)${NC}"
        FAILED=$((FAILED + 1))
        FAILED_TESTS="$FAILED_TESTS\n$test_file (LLC)"
        continue
    fi

    # Link to Executable
    $GCC "$o_file" -o "$exe_file" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}FAILED (Linking)${NC}"
        FAILED=$((FAILED + 1))
        FAILED_TESTS="$FAILED_TESTS\n$test_file (Linking)"
        continue
    fi

    # Run Executable
    "./$exe_file" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}PASSED${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAILED (Runtime: $?)${NC}"
        FAILED=$((FAILED + 1))
        FAILED_TESTS="$FAILED_TESTS\n$test_file (Runtime)"
    fi

    # Cleanup
    rm -f "$ll_file" "$o_file" "$exe_file"
done

# Special case for test_interop.nov
echo -n "Testing tests/test_interop.nov (with C wrapper)... "
$NOVUSC tests/test_interop.nov > /dev/null 2>&1
mv test_interop.ll tests/test_interop.ll
$LLC tests/test_interop.ll -relocation-model=pic -filetype=obj -o tests/test_interop.o > /dev/null 2>&1
$GCC tests/test_interop.o tests/wrapper.c -o tests/test_interop_exe > /dev/null 2>&1
"./tests/test_interop_exe" > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "${GREEN}PASSED${NC}"
    PASSED=$((PASSED + 1))
else
    echo -e "${RED}FAILED${NC}"
    FAILED=$((FAILED + 1))
    FAILED_TESTS="$FAILED_TESTS\ntests/test_interop.nov"
fi
rm -f tests/test_interop.ll tests/test_interop.o tests/test_interop_exe

echo "---------------------------"
echo -e "Summary: ${GREEN}$PASSED passed${NC}, ${RED}$FAILED failed${NC}"

if [ $FAILED -ne 0 ]; then
    echo -e "Failed tests: $FAILED_TESTS"
    exit 1
fi

exit 0
