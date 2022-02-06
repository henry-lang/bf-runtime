cmake_minimum_required(VERSION 3.16)
project(bf C)

set(CMAKE_C_STANDARD 99)

add_executable(bf src/main.c src/program.c src/program.h src/log.c src/log.h src/op.c src/op.h src/parse.c src/parse.h src/optimize.c src/optimize.h)
