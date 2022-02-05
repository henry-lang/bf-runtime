#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "op.h"

typedef struct BFConfig {
    char* filename;
    
    size_t memory_size;
    size_t stack_size;
} BFConfig;

typedef struct BFProgram {
    BFConfig config;

    BFOpArray ops;

    char* memory;
    char* ptr;
} BFProgram;

BFProgram bf_construct(BFConfig config);
void bf_run(BFProgram* program);
void bf_free(BFProgram* program);