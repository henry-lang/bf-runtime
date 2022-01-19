#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "program.h"
#include "log.h"

BFProgram bf_construct(BFConfig config) {
    BFProgram program;
    program.config = config;

    bf_log_info(config.filename, "Constructing: Opening file.");
    FILE* file = fopen(config.filename, "r");
    if(file == NULL) {
        if(!strcmp(config.filename, "main.bf")) {
            bf_log_error(config.filename, "Failed to open file. This may be because you didn't specify a file and it defaults to main.bf.");
        } else {
            bf_log_error(config.filename, "Failed to open file.");
        }
    }

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    program.source = malloc(sizeof(char) * (size + 1));
    if(program.source == NULL) {
        bf_log_error(config.filename, "Failed to allocate file source.");
    }

    program.size = size;

    if(fread(program.source, sizeof(char), size, file) == 1) {
        bf_log_error(config.filename, "Failed to read file source.");
    }
    program.source[size] = '\0';
    program.current = program.source;
    fclose(file);

    bf_log_info(config.filename, "Constructing: Allocating program resources.");
    program.memory = malloc(sizeof(char) * config.memory_size);
    program.cell = program.memory;
    if(program.memory == NULL) {
        bf_log_error(config.filename, "Failed to allocate program memory.");
    }
    memset(program.memory, 0, config.memory_size);

    program.stack = malloc(sizeof(char*) * config.stack_size);
    program.stack_pointer = *(program.stack);
    if(program.stack == NULL) {
        bf_log_error(config.filename, "Failed to allocate program stack.");
    }

    bf_log_info(config.filename, "Finished Constructing");

    bf_validate(&program);

    return program;
}

void bf_validate(BFProgram* program) {
    bf_log_info(program->config.filename, "Validating: Parsing file for errors.");

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
        bf_log_error(program->config.filename, "Syntax Error: Mismatched brackets.");
    }

    bf_log_info(program->config.filename, "Finished Validating");
    bf_log_info(program->config.filename, "Program output will be shown below.\n");
}

void bf_run(BFProgram* program) {
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
    free(program->memory);
    free(program->stack);
}
