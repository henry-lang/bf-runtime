#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "program.h"
#include "log.h"
#include "parse.h"
#include "optimize.h"

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

    BFOps unoptimized = bf_parse(source, length);
    program.ops = bf_optimize(&unoptimized);
//    bf_ops_print(&program.ops);
    bf_ops_free(&unoptimized);

    program.memory = malloc(sizeof(char) * config.memory_size);
    program.ptr = program.memory;
    if(program.memory == NULL) {
        bf_log_error("Failed to allocate program memory.");
    }
    memset(program.memory, 0, config.memory_size);

    free(source);
    return program;
}

void bf_free(BFProgram* program) {
    bf_ops_free(&program->ops);
    free(program->memory);
}
