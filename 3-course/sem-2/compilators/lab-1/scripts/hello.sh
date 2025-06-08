#!/bin/bash
set -e

source scripts/source/messages.sh

print_start

# Go to the project folder
cd /project/dragon-tiger

# Create a test Tiger file with a simple print statement
cp ../scripts/source/hello.tig.template hello.tig

print_compile

# Compile the Tiger file to an object file
src/driver/dtiger -o hello.o hello.tig

print_link

# Link the object file with the runtime library to create an executable
clang++ hello.o src/runtime/posix/libruntime.a -o hello -no-pie

print_run

# Run the compiled program
./hello
