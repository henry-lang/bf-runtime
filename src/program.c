#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "program.h"
#include "log.h"
#include "parse.h"

BFProgram bf_construct(BFConfig config) {
    BFProgram program;
    program.config = config;

    bf_log_info("Constructing: Opening file.");
    FILE *file = fopen(config.filename, "r");
    if (file == NULL) {
        if (!strcmp(config.filename, "main.bf")) {
            bf_log_error("Failed to open file. This may be because you didn't specify a file and it defaults to main.bf.");
        } else {
            bf_log_error("Failed to open file.");
        }
    }

    fseek(file, 0L, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *source = malloc(sizeof(char) * (length + 1));
    if (source == NULL) {
        bf_log_error("Failed to allocate file source.");
    }

    if (fread(source, sizeof(char), length, file) == 1) {
        bf_log_error("Failed to read file source.");
    }
    source[length] = '\0';
    fclose(file);

    program.ops = bf_parse(source, length);

//    bf_log_info(config.filename, "Constructing: Allocating program resources.");
    program.memory = malloc(sizeof(char) * config.memory_size);
    program.ptr = program.memory;
    if(program.memory == NULL) {
        bf_log_error("Failed to allocate program memory.");
    }
    memset(program.memory, 0, config.memory_size);

    free(source);
    return program;
}

void bf_run(BFProgram* program) {
//    while(*(program->current) != '\0') {
//        char token = *(program->current);
//
//        switch (token) {
//            default: break;
//
//            case '>': {
//                ++program->cell;
//                break;
//            }
//
//            case '<': {
//                --program->cell;
//                break;
//            }
//
//            case '+': {
//                ++*(program->cell);
//                break;
//            }
//
//            case '-': {
//                --*(program->cell);
//                break;
//            }
//
//            case '.': {
//                putchar(*(program->cell));
//                break;
//            }
//
//            case ',': {
//                *(program->cell) = (char) getchar();
//                break;
//            }
//
//            case '[': {
//                if(*(program->cell) == 0) {
//                    while(*(program->current) != ']') { // Loop until we find matching bracket.
//                        ++program->current;
//                    }
//                    continue;
//                }
//
//                ++program->stack_pointer;
//                program->stack_pointer = program->current;
//
//                break;
//            }
//
//            case ']': {
//                if(*(program->cell) != 0) {
//                    program->current = program->stack_pointer;
//                    continue;
//                }
//
//                *(program->stack_pointer) = 0;
//                --program->stack_pointer;
//
//                break;
//            }
//        }
//    }
}

void bf_free(BFProgram* program) {
    bf_op_array_free(&program->ops);
    free(program->memory);
}
