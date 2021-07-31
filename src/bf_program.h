//
// Created by henry on 7/28/21.
//

#ifndef BF_INTERPRETER_BF_PROGRAM_H
#define BF_INTERPRETER_BF_PROGRAM_H

// We want to use logging to show what's going on
#define BF_LOGGING
// #define BF_UNIDENTIFIED_SYMBOL_ERROR

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#define BF_DEFAULT_MEMORY 3000
#define BF_DEFAULT_STACK 100

typedef struct {
    char* source;
    char* filename;
    size_t size;

    char* current;

    char* memory;
    char* cell;
    size_t memory_size;

    char** stack;
    char* stack_pointer;
    size_t stack_size;
} BFProgram;

BFProgram bf_construct(char* filename, size_t memory_size, size_t stack_size);
void bf_validate(BFProgram* program);
void bf_interpret(BFProgram* program);
void bf_free(BFProgram* program);

static inline void bf_log_info(char* filename, char* message) {
#ifdef BF_LOGGING
    printf("[INFO | %s] %s\n", filename, message);
#endif
}

static inline void bf_logf_info(char* filename, char* format, ...) {
#ifdef BF_LOGGING
    va_list args;
    va_start(args, format);
    printf("[INFO | %s] ", filename);
    vprintf(format, args);
    va_end(args);
#endif
}

static inline void bf_log_error(char* filename, char* message) {
#ifdef BF_LOGGING
    printf("\033[31;1m[ERROR | %s] %s\033[0m\n", filename, message);
#endif
    exit(1);
}

static inline void bf_logf_error(char* filename, char* format, ...) {
#ifdef BF_LOGGING
    va_list args;
    va_start(args, format);
    printf("\033[31;1m[ERROR | %s]", filename);
    vprintf(format, args);
    printf("\033[0m\n");
    va_end(args);
#endif
    exit(1);
}

static inline void bf_log_warn(char* filename, char* message) {
#ifdef BF_LOGGING
    printf("\033[33m[WARN | %s] %s\033[0m\n", filename, message);
#endif
}

static inline void bf_logf_warn(char* filename, char* format, ...) {
#ifdef BF_LOGGING
    va_list args;
    va_start(args, format);
    printf("\033[33m[WARN | %s] ", filename);
    vprintf(format, args);
    printf("\033[0m\n");
    va_end(args);
#endif
}

#endif
