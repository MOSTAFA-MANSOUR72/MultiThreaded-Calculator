# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and C standard
project(MultiThreadCalculator VERSION 1.0 C)
set(CMAKE_C_STANDARD 11)

# Add the executable target
add_executable(${MultiThreaded-Calculator} ${MultiThreadCalculator.c})

# Link pthread library for multithreading
target_link_libraries(${MultiThreaded-Calculator} pthread)
