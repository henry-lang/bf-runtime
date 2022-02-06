#!/bin/sh
gcc src/main.c src/program.c src/log.c src/op.c src/parse.c src/optimize.c
#find src -name "*.gch" | xargs rm
