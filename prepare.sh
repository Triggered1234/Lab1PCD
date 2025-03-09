#!/bin/bash

# Step 1: Install dependencies with Conan
echo "Installing dependencies with Conan..."
conan install . --build=missing

# Step 2: Create a build directory if it doesn't exist and navigate into it
echo "Setting up build directory..."
mkdir -p build
cd build

# Step 3: Ensure CMake can find Conan-generated files
# CMake needs to be aware of the toolchain file and the generator directory
export CMAKE_PREFIX_PATH=$(pwd)/generators

# Step 4: Configure the project with CMake
echo "Configuring project with CMake..."
# Note the change here - use 'generators/conan_toolchain.cmake' (not Release/generators)
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake

cd ../

# Step 5: Build the project
echo "Building project..."
cmake --build . --config Release

# Step 6: Check the build directory structure
echo "Build directory structure:"
ls -l Release

# Step 7: Run the executable (adjusted to match 'app1' executable)
echo "Running the project..."
# Check if 'Release/app1' exists
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

# End of script
echo "Project run completed."
