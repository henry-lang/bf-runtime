/* Brainf**k interpreter by Henry Langmack | 11/23/2020 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "bf_program.h"

int main(int argc, char** argv) {
    if(argc == 1) {
        bf_log_error("?", "No file supplied to run.");
    } else if(argc != 2) {
        bf_log_error("?", "Unexpected number of arguments.");
    }

    char* file_name = argv[1];

    BFProgram program = bf_construct(file_name, BF_DEFAULT_MEMORY, BF_DEFAULT_STACK);

    bf_validate(&program);
    bf_interpret(&program);
    bf_free(&program);
}
