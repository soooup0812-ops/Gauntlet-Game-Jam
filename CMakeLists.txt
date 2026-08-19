cmake_minimum_required(VERSION 3.14)
project(Ambatutoss CXX)

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
add_executable(Ambatutoss main.cpp Stone.cpp Hand.cpp Variables.cpp Game.cpp)

# Link Raylib to your executable
target_link_libraries(Ambatutoss PRIVATE raylib)