#include <stdio.h>
#include <stdint.h>

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
        stack->capacity *= 2;
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

BFOpArray bf_parse(const char* source, size_t length) {
    BFOpArray op_array = bf_op_array_init(1);

    for(size_t i = 0; i < length; i++) {
        switch(source[i]) {
            case '+':
            case '-': {
                intmax_t count = source[i] == '+' ? 1 : -1;

                while(source[++i] == '+' || source[i] == '-' && i < length) {
                    count += source[i] == '+' ? 1 : -1;
                }

                if(count != 0) {
                    bf_op_array_append(&op_array, (BFOp) {
                        .type = CHANGE,
                        .value = {
                            .int_val = count
                        }
                    });
                }
                break;
            }
            case '>': {
                intmax_t count = source[i] == '>' ? 1 : -1;

                while(source[++i] == '>' || source[i] == '<' && i < length) {
                    count += source[i] == '>' ? 1 : -1;
                }

                if(count != 0) {
                    bf_op_array_append(&op_array, (BFOp) {
                        .type = MOVE,
                        .value = {
                            .int_val = count
                        }
                    });
                }
                break;
            }
        }
    }

//    for(size_t i = 0; i < op_array.length; i++) {
//        printf("%u %jd\n", op_array.ops[1].type, op_array.ops[i].value.int_val);
//    }

    return op_array;
}
