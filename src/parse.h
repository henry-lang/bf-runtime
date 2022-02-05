#pragma once

#include "op.h"

typedef struct BFJumpStack {
    size_t* jumps;
    size_t length;
    size_t capacity;
} BFJumpStack;

BFJumpStack bf_jump_stack_init(size_t length);
void bf_jump_stack_push(BFJumpStack* stack, size_t index);
size_t bf_jump_stack_pop(BFJumpStack* stack);
void bf_jump_stack_free(BFJumpStack* stack);

BFOpArray bf_parse(const char* source, size_t length);
