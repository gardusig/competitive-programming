cmake_minimum_required(VERSION 3.0)

set(COMPETITIVE_PROGRAMMING_FLAGS, "-Wall -O3 -std=c++17")
set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} ${COMPETITIVE_PROGRAMMING_FLAGS}")

project(main)

add_executable(main main.cpp)

