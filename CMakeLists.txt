cmake_minimum_required(VERSION 3.19)
project(bf C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /bin/)

set(CMAKE_C_STANDARD 99)

add_executable(bf src/main.c src/bf_program.c src/bf_program.h)