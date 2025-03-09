#!/bin/bash

# Step 1: Install dependencies with Conan
echo "Installing dependencies with Conan..."
conan install . --build=missing

# Step 2: Create a build directory if it doesn't exist and navigate into it
echo "Setting up build directory..."
mkdir -p build
cd build

# Step 3: Ensure CMake can find Conan-generated files
export CMAKE_PREFIX_PATH=$(pwd)/generators

# Step 4: Configure the project with CMake
echo "Configuring project with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake

# Step 5: Build the project
echo "Building project..."
cmake --build . --config Release

# Step 6: Run the executable (assuming the name is 'test' and built in 'Release' folder)
echo "Running the project..."
./Release/test  # Adjust if the actual path is different

# End of script
echo "Project run completed."
