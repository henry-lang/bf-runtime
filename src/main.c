/* Brainf**k interpreter by henry-lang */

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "program.h"
#include "op.h"
#include "log.h"

bool is_option(char* str) {
    if(strlen(str) > 3 && str[0] == '-' && str[1] == '-') return true;

    return false;
}

void handle_option(BFConfig* config, char* opt) {
    if(!strcmp(opt, "--verbose")) {
        BF_LOG_VERBOSE = true;
    } else if(!strncmp(opt, "--mem-size=", 11)) {
        char* mem_size_str = opt + 11;
        config->memory_size = (size_t) strtoumax(mem_size_str, NULL, 10);
    } else if(!strncmp(opt, "--stack-size=", 13)) {
        char* stack_size_str = opt + 13;
        config->stack_size = (size_t) strtoumax(stack_size_str, NULL, 10);
    } else {
        bf_logf_error("?", "Unknown option: %s.", opt);
    }
}

int main(int argc, char** argv) {
    BFConfig config = {
        .filename = "main.bf",

        .memory_size = 30000,
        .stack_size = 128
    };

    for(int i = 1; i < argc; i++) {
        if (is_option(argv[i])) {
            handle_option(&config, argv[i]);
        } else {
            config.filename = argv[i];
        }
    }

    BF_LOG_FILENAME = config.filename;
    BFProgram program = bf_construct(config);
    bf_run(&program);
    bf_free(&program);
}
