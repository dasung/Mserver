#!/bin/bash

# Create the build directory if it doesn't exist
mkdir -p build

# Navigate into the build directory
cd build

# Run CMake to configure the project
echo "cmaking Donga..."
cmake ..

# Build the project using Ninja
echo "making Donga..."
ninja

cd ../bin
# Run the executable with --no-window argument
echo "runing Donga in silent mode..."
./Donga.exe --no-window
#./Donga.exe

cd ..
echo "done!"