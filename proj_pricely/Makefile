# Path to the BuildIt repository
BUILDIT_PATH = deps/buildit

GTEST_INCLUDE = -Ideps/gtest/googletest/include
GTEST_LIB = deps/gtest/build/lib/libgtest.a deps/gtest/build/lib/libgtest_main.a -pthread
INCLUDE = -Iinclude -Ideps/gtest/googletest/include


# Compiler and flags
CXX = g++
CXX_STANDARD = -std=c++11
CXX_FLAGS = -O3

# Source files and include directories
SRC = src/a.cpp src/main.cpp
INCLUDE = -Iinclude

# Output directory and executable
BUILD_DIR = build
OUTPUT = $(BUILD_DIR)/main

# Flags retrieved from BuildIt
COMPILE_FLAGS = $(shell make --no-print-directory -C $(BUILDIT_PATH) compile-flags)
LINKER_FLAGS = $(shell make --no-print-directory -C $(BUILDIT_PATH) linker-flags)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilation rule
$(OUTPUT): $(BUILD_DIR) $(SRC)
	$(CXX) $(CXX_STANDARD) $(COMPILE_FLAGS) $(INCLUDE) $(SRC) $(LINKER_FLAGS) $(CXX_FLAGS) -o $(OUTPUT)

# Default target
all: $(OUTPUT)

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
