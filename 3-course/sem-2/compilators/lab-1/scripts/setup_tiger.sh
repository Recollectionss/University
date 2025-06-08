#!/bin/bash
set -e

# Go to the project folder
cd /project/dragon-tiger

# Create a test Tiger file with a simple print statement
echo 'print("Hello World!\n")' > test.tig

# Compile the Tiger file to an object file
src/driver/dtiger -o test.o test.tig

# Link the object file with the runtime library to create an executable
clang++ test.o src/runtime/posix/libruntime.a -o test -no-pie

# Run the compiled program
./test

