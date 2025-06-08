#!/bin/bash
set -e

source scripts/source/messages.sh

print_start

# Go to the project folder
cd /project/dragon-tiger

cp ../scripts/source/fibonacci.tig.template fibonacci.tig

print_compile

# Compile the Tiger file to an object file
src/driver/dtiger -o fibonacci.o fibonacci.tig

print_link

clang++ fibonacci.o src/runtime/posix/libruntime.a -o fibonacci -no-pie

print_run 

# Run the compiled program
./fibonacci
