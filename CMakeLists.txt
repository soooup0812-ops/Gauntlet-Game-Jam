cmake_minimum_required(VERSION 3.14)
project(Ambatu CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically download and include Raylib using FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Create your executable
add_executable(Ambatu main.cpp Stone.cpp)

# Link Raylib to your executable
target_link_libraries(Ambatu PRIVATE raylib)