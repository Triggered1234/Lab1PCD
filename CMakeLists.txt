cmake_minimum_required(VERSION 3.23)

project(PCD_LAB1)

add_executable(app1 src/app1.c)
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/generators")
# add_executable(app2, src/app2.c)
# add_executable(app3, src/app3.c)

# find_package(ZLIB REQUIRED)
find_package(Argtable3 REQUIRED)
find_package(popt REQUIRED)
# message("FOUND zlib at ${ZLIB_INCLUDE_DIRS} with libs ${ZLIB_LIBRARIES}")

# target_include_directories(app1 PUBLIC ${ZLIB_INCLUDE_DIRS})
# target_link_libraries(app1 PUBLIC ${ZLIB_LIBRARIES})

target_link_libraries(app1 PUBLIC argtable3::argtable3)
target_link_libraries(app1 PRIVATE popt::popt)
