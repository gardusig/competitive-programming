cmake_minimum_required(VERSION 3.0)

set(COMPETITIVE_PROGRAMMING_FLAGS, "-Wall -O3 -std=c++14")

set(CMAKE_C_COMPILER "/usr/local/bin/gcc-9")
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-9")
set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} ${COMPETITIVE_PROGRAMMING_FLAGS}")

project(test)

add_executable(test main.cpp)