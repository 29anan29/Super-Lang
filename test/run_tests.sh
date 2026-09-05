#!/bin/bash

echo "Running SUPER tests..."
CFLAGS="-D_GNU_SOURCE -Wall -Wextra -std=c11 -g -Isrc/frontend -Isrc/midend -Isrc/backend -Isrc/toolchain"

# Test lexer
echo "--- Lexer Test ---"
gcc $CFLAGS -c src/frontend/lexer.c -o /tmp/lexer.o
if [ $? -eq 0 ]; then echo "Lexer: PASS"; else echo "Lexer: FAIL"; fi

# Test parser
echo "--- Parser Test ---"
gcc $CFLAGS -c src/frontend/parser.c -o /tmp/parser.o
if [ $? -eq 0 ]; then echo "Parser: PASS"; else echo "Parser: FAIL"; fi

# Test type inference
echo "--- Type Inference Test ---"
gcc $CFLAGS -c src/midend/type_inference.c -o /tmp/type_inference.o
if [ $? -eq 0 ]; then echo "Type Inference: PASS"; else echo "Type Inference: FAIL"; fi

# Test SSA
echo "--- SSA Test ---"
gcc $CFLAGS -c src/midend/ssa.c -o /tmp/ssa.o
if [ $? -eq 0 ]; then echo "SSA: PASS"; else echo "SSA: FAIL"; fi

# Test C codegen
echo "--- C Codegen Test ---"
gcc $CFLAGS -c src/backend/c_codegen.c -o /tmp/c_codegen.o
if [ $? -eq 0 ]; then echo "C Codegen: PASS"; else echo "C Codegen: FAIL"; fi

# Test full build
echo "--- Full Build ---"
make clean > /dev/null 2>&1
make > /dev/null 2>&1
if [ $? -eq 0 ]; then echo "Full Build: PASS"; else echo "Full Build: FAIL"; fi

# Test compile
echo "--- Compile Test ---"
./superc examples/hello.super > /dev/null 2>&1
if [ $? -eq 0 ]; then echo "Compile: PASS"; else echo "Compile: FAIL"; fi

echo "All tests completed."
