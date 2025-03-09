#!/bin/bash

echo "Installing dependencies with Conan..."
conan install . --build=missing

echo "Setting up build directory..."
mkdir -p build
cd build

export CMAKE_PREFIX_PATH=$(pwd)/generators

echo "Configuring project with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake

cd ../

echo "Building project..."
cmake --build . --config Release

echo "Build directory structure:"
ls -l Release

echo "Running the project..."
if [ -f "./Release/app1" ]; then
    ./Release/app1
else
    echo "Executable app1 not found in Release folder!"
fi

if [ -f "./Release/app2" ]; then
    ./Release/app2
else
    echo "Executable app2 not found in Release folder!"
fi

if [ -f "./Release/app3" ]; then
    ./Release/app3
else
    echo "Executable app3 not found in Release folder!"
fi

echo "Project run completed."
