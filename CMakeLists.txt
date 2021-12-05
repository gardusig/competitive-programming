cmake_minimum_required(VERSION 3.20)
project(competitive_programming)

add_compile_options(
   -O3
   -pedantic
   -std=c++17
   -Wall
   -Werror
   -Wextra
   -Wl,-stack_size -Wl,10000000
)

include(CTest)

add_subdirectory("src")
add_subdirectory("tst")
