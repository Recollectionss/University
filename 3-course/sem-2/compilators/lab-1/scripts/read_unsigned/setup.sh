#!/bin/bash
set -e

source scripts/source/messages.sh

print_start

# Go to the project folder
cd /project/dragon-tiger

# Create a test Tiger file with a simple print statement
cp ../scripts/source/read_unsigned.tig.template read_unsigned.tig

print_compile

# Compile the Tiger file to an object file
src/driver/dtiger -o read_unsigned.o read_unsigned.tig

print_link

# Link the object file with the runtime library to create an executable
clang++ read_unsigned.o src/runtime/posix/libruntime.a -o read_unsigned -no-pie
