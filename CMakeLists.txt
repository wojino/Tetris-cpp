# CMake version
cmake_minimum_required(VERSION 3.0)

# Declare project
project(Tetris-CPP)

# Define
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/Includes/Tetris)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Sources/Tetris)

# Headers
include_directories(
    ${HEADER_DIR}/Helpers
    ${HEADER_DIR}/Modes
)

# Sources
file(GLOB_RECURSE SOURCES
    ${SOURCE_DIR}/*.cpp)



# Compile options
add_compile_options(-Wall -std=c++11 -O2)

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp ${SOURCES})