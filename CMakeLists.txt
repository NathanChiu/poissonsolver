cmake_minimum_required(VERSION 3.7)
project(poissonsolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/solver.cpp src/solver.h)
add_executable(poissonsolver ${SOURCE_FILES})