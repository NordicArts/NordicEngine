# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(MiniZ)

# Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

# Directory
include_directories(${PROJECT_SOURCE_DIR})

# Set Source
set(LibSources ${PROJECT_SOURCE_DIR}/miniz.c)

# Compile
add_library(MiniZ SHARED ${LibSources})
set_target_properties(MiniZ PROPERTIES OUTPUT_NAME "MiniZ")
