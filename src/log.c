#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>

#include "log.h"

bool BF_LOG_VERBOSE = false;

void bf_log_info(char* filename, char* message) {
    if(BF_LOG_VERBOSE) {
        printf("[INFO | %s] %s\n", filename, message);
    }
}

void bf_logf_info(char* filename, char* format, ...) {
    if(BF_LOG_VERBOSE) {
        va_list args;
        va_start(args, format);
        printf("[INFO | %s] ", filename);
        vprintf(format, args);
        va_end(args);
    }
}

void bf_log_warn(char* filename, char* message) {
    printf("\033[33m[WARN | %s] %s\033[0m\n", filename, message);
}

void bf_logf_warn(char* filename, char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[33m[WARN | %s] ", filename);
    vprintf(format, args);
    printf("\033[0m\n");
    va_end(args);
}

void bf_log_error(char* filename, char* message) {
    printf("\033[31;1m[ERROR | %s] %s\033[0m\n", filename, message);

    exit(1);
}

void bf_logf_error(char* filename, char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[31;1m[ERROR | %s] ", filename);
    vprintf(format, args);
    printf("\033[0m\n");
    va_end(args);

    exit(1);
}

