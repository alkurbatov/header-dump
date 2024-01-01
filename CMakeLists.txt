cmake_minimum_required(VERSION 3.15)

project(header-dump)

set(CMAKE_CXX_STANDARD 20)

# Specify output directories
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# bot sources
add_subdirectory(src)
