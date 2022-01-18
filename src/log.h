#include <stdbool.h>

#ifndef BF_LOG_H
#define BF_LOG_H

extern bool BF_LOG_VERBOSE;

void bf_log_info(char* filename, char* message);
void bf_logf_info(char* filename, char* format, ...);

void bf_log_warn(char* filename, char* message);
void bf_logf_warn(char* filename, char* format, ...);

void bf_log_error(char* filename, char* mesasge);
void bf_logf_error(char* filename, char* format, ...);

#endif
