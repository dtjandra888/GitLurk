#!/bin/bash

set -e

BUILD_DIR="build"

cmake -B $BUILD_DIR -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo -e "\nFinished CMake;\n"

make -C $BUILD_DIR

echo -e "\n Finished building\n"
