#!/bin/bash

# Path to the BuildIt repository
BUILDIT_PATH="deps/buildit"

# Ensure the build directory exists
mkdir -p build

# Compile command with the added include path and csv_loader.cpp
g++ -std=c++11 $(make --no-print-directory -C $BUILDIT_PATH compile-flags) \
    -Iinclude src/a.cpp src/main.cpp \
    $(make --no-print-directory -C $BUILDIT_PATH linker-flags) -O3 -o build/main

echo "Compilation complete. Executable created at build/main"
