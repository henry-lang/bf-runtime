//
// Created by henry on 7/28/21.
//

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "bf_program.h"

BFProgram bf_construct(char* filename, size_t memory_size, size_t stack_size) {
    bf_log_info(filename, "Constructing");
    BFProgram program;

    bf_log_info(filename, "Constructing: Opening file.");
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        bf_log_error(filename, "Failed to open file.");
    }
    // Calculate program's size
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    program.source = malloc(sizeof(char) * (size + 1));
    if(program.source == NULL) {
        bf_log_error(filename, "Failed to allocate file source.");
    }

    program.filename = malloc(sizeof(char) * (strlen(filename) + 1));
    if(program.filename == NULL) {
        bf_log_error(filename, "Failed to allocate file name. Why?");
    }
    strcpy(program.filename, filename);

    program.size = size;
    // Copy file into source memory
    if(fread(program.source, sizeof(char), size, file) == 1) {
        bf_log_error(filename, "Failed to read file source.");
    }
    program.source[size] = '\0';
    program.current = program.source;
    fclose(file);

    bf_log_info(filename, "Constructing: Allocating program resources.");
    program.memory = malloc(sizeof(char) * memory_size);
    program.cell = program.memory;
    if(program.memory == NULL) {
        bf_log_error(filename, "Failed to allocate program memory.");
    }
    memset(program.memory, 0, memory_size);
    program.memory_size = memory_size;

    program.stack = malloc(sizeof(char*) * stack_size);
    program.stack_pointer = *(program.stack);
    if(program.stack == NULL) {
        bf_log_error(filename, "Failed to allocate program stack.");
    }
    program.stack_size = stack_size;


    bf_log_info(filename, "Finished Constructing");
    return program;
}

void bf_validate(BFProgram* program) {
    bf_log_info(program->filename, "Validating");
    bf_log_info(program->filename, "Validating: Parsing file for errors.");

    char cur;
    int bracket_count = 0;

    for(int i = 0; i < program->size; i++) {
        cur = program->source[i];
        switch(cur) {
            default: {
#ifdef BF_UNIDENTIFIED_SYMBOL_ERROR
                bf_logf_error(program->filename, "%s\n%s%c\n%s%d",
					"Syntax Error: Unidentified Symbol.",
					"Symbol: ",
					cur,
					"Position: ",
					i + 1
				);
#endif
                break;
            }

            case '[': {
                bracket_count++;
                break;
            }

            case ']': {
                bracket_count--;
                break;
            }

            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',': {
                break;
            }
        }
    }

    if(bracket_count != 0) {
        bf_log_error(program->filename, "Syntax Error: Mismatched brackets.");
    }

    bf_log_info(program->filename, "Finished Validating");
    bf_log_info(program->filename, "Program output will be shown below.\n\n");
}

void bf_interpret(BFProgram* program) {
    while(*(program->current) != '\0') {
        char token = *(program->current);

        switch (token) {
            default: break;

            case '>': {
                ++program->cell;
                break;
            }

            case '<': {
                --program->cell;
                break;
            }

            case '+': {
                ++*(program->cell);
                break;
            }

            case '-': {
                --*(program->cell);
                break;
            }

            case '.': {
                putchar(*(program->cell));
                break;
            }

            case ',': {
                *(program->cell) = (char) getchar();
                break;
            }

            case '[': {
                if(*(program->cell) == 0) {
                    while(*(program->current) != ']') { // Loop until we find matching bracket.
                        ++program->current;
                    }
                    continue;
                }

                ++program->stack_pointer;
                program->stack_pointer = program->current;

                break;
            }

            case ']': {
                if(*(program->cell) != 0) {
                    program->current = program->stack_pointer;
                    continue;
                }

                *(program->stack_pointer) = 0;
                --program->stack_pointer;

                break;
            }
        }

        ++program->current;
    }
}

void bf_free(BFProgram* program) {
    free(program->source);
    free(program->filename);
    free(program->memory);
    free(program->stack);
}