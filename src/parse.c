#include <stdio.h>

#include "parse.h"
#include "op.h"
#include "log.h"

BFJumpStack bf_jump_stack_init(size_t capacity) {
    return (BFJumpStack) {
        .jumps = malloc(sizeof(BFOp) * capacity),
        .length = 0,
        .capacity = capacity
    };
}

void bf_jump_stack_push(BFJumpStack* stack, size_t jump) {
    if(stack->length == stack->capacity) {
        stack->capacity = stack->capacity == 0 ? 1 : stack->capacity * 2;
        stack->jumps = realloc(stack->jumps, stack->capacity * sizeof(BFOp));
    }
    stack->jumps[stack->length++] = jump;
}

size_t bf_jump_stack_pop(BFJumpStack* stack) {
    if(stack->length == 0) {
        bf_log_error("Unexpected closing bracket.");
    }

    return stack->jumps[stack->length-- - 1];
}

void bf_jump_stack_free(BFJumpStack* stack) {
    free(stack->jumps);
}

BFOps bf_parse(const char* source, size_t length) {
    BFOps op_array = bf_ops_init(length);

    for(size_t i = 0; i < length; i++) {
        switch(source[i]) {
            case '+': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = CHANGE,
                        .value = 1
                });
                break;
            }
            case '-': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = CHANGE,
                        .value = -1
                });
                break;
            }
            case '>': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = MOVE,
                        .value = 1
                });
                break;
            }
            case '<': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = MOVE,
                        .value = -1
                });
                break;
            }
            case '[': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = JUMP_ZERO,
                        .value = 0 // Temporary
                });
                break;
            }
            case ']': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = JUMP_NONZERO,
                        .value = 0 // Temporary
                });
                break;
            }
            case '.': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = PUT,
                        .value = 1
                });
                break;
            }
            case ',': {
                bf_ops_append(&op_array, (BFOp) {
                        .type = GET,
                        .value = 1
                });
                break;
            }
        }
    }

    return op_array;
}
