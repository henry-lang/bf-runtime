#ifndef BF_PROGRAM_H
#define BF_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BFConfig {
    char* filename;
    
    size_t memory_size;
    size_t stack_size;
} BFConfig;

typedef struct BFProgram {
    BFConfig config;

    char* source;
    size_t size;

    char* current;

    char* memory;
    char* cell;

    char** stack;
    char* stack_pointer;
} BFProgram;

BFProgram bf_construct(BFConfig config);
void bf_validate(BFProgram* program);
void bf_run(BFProgram* program);
void bf_free(BFProgram* program);

#endif
