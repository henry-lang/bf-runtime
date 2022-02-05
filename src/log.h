#pragma once

#include <stdbool.h>

extern bool BF_LOG_VERBOSE;
extern char* BF_LOG_FILENAME;

void bf_log_info(char* message);
void bf_logf_info(char* format, ...);

void bf_log_warn(char* message);
void bf_logf_warn(char* format, ...);

void bf_log_error(char* mesasge);
void bf_logf_error(char* format, ...);
