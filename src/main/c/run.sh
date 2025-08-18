#!/bin/bash

# Output executable name (default: a.out)
OUTPUT=${1:-a.out}

# Find all .c files recursively
C_FILES=$(find . -type f -name "*.c")

# Check if any .c files were found
if [ -z "$C_FILES" ]; then
  echo "No .c files found in current directory or subdirectories."
  exit 1
fi

# Compile and link all C files into the executable
gcc -g $C_FILES -o "$OUTPUT"

if [ $? -eq 0 ]; then
  echo "Compilation successful. Executable created: $OUTPUT"
else
  echo "Compilation failed."
fi