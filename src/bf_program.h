//
// Created by henry on 7/28/21.
//

#ifndef BF_PROGRAM_H
#define BF_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BF_DEFAULT_MEMORY 3000
#define BF_DEFAULT_STACK 100

typedef struct {
    char* filename;
    
    size_t memory_size;
    size_t stack_size;
} BFConfig;

typedef struct {
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
void bf_interpret(BFProgram* program);
void bf_free(BFProgram* program);

#endif
