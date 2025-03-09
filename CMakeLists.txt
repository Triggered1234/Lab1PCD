cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/build/Release/generators/conan_toolchain.cmake" CACHE FILEPATH "Toolchain file")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(PCD_LAB1 C)

find_package(CURL REQUIRED)

set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/build/Release/generators")
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/build/Release/generators")

add_executable(app1 src/app1.c)
add_executable(app2 src/app2.c)
add_executable(app3 src/app3.c)

target_link_libraries(app3 PRIVATE CURL::libcurl)