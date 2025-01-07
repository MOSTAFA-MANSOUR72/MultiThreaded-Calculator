# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and C standard
project(MultiThreadCalculator VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 99)

# Define the source files
set(SOURCES
    src/main.c
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link pthread library for multithreading
target_link_libraries(${PROJECT_NAME} pthread)
