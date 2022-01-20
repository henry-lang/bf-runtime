#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>

#include "log.h"

bool BF_LOG_VERBOSE = false;
char* BF_LOG_FILENAME = "?";

void bf_log_info(char* message) {
    if(BF_LOG_VERBOSE) {
        printf("[INFO | %s] %s\n", BF_LOG_FILENAME, message);
    }
}

void bf_logf_info(char* format, ...) {
    if(BF_LOG_VERBOSE) {
        va_list args;
        va_start(args, format);
        printf("[INFO | %s] ", BF_LOG_FILENAME);
        vprintf(format, args);
        va_end(args);
    }
}

void bf_log_warn(char* message) {
    printf("\033[33m[WARN | %s] %s\033[0m\n", BF_LOG_FILENAME, message);
}

void bf_logf_warn(char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[33m[WARN | %s] ", BF_LOG_FILENAME);
    vprintf(format, args);
    printf("\033[0m\n");
    va_end(args);
}

void bf_log_error(char* message) {
    printf("\033[31;1m[ERROR | %s] %s\033[0m\n", BF_LOG_FILENAME, message);

    exit(1);
}

void bf_logf_error(char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[31;1m[ERROR | %s] ", BF_LOG_FILENAME);
    vprintf(format, args);
    printf("\033[0m\n");
    va_end(args);

    exit(1);
}

