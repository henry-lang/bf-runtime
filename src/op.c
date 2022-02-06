#include <stdlib.h>
#include <stdio.h>

#include "op.h"

char* bf_op_str(BFOpType type) {
    switch(type) {
        default: return NULL;
        case CHANGE: return "CHANGE";
        case MOVE: return "MOVE";
        case SET_ZERO: return "SET_ZERO";
        case JUMP_ZERO: return "JUMP_ZERO";
        case JUMP_NONZERO: return "JUMP_NONZERO";
        case PUT: return "PUT";
        case GET: return "GET";
    }
}

BFOps bf_ops_init(size_t capacity) {
    return (BFOps) {
        .ops = malloc(sizeof(BFOp) * capacity),
        .length = 0,
        .capacity = capacity
    };
}

void bf_ops_append(BFOps* op_array, BFOp op) {
    if(op_array->length == op_array->capacity) {
        op_array->capacity *= 2;
        op_array->ops = realloc(op_array->ops, op_array->capacity * sizeof(BFOp));
    }
    op_array->ops[op_array->length++] = op;
}

void bf_ops_print(BFOps* op_array) {
    for(size_t i = 0; i < op_array->length; i++) {
        printf("%s: %lld\n", bf_op_str(op_array->ops[i].type), op_array->ops[i].value);
    }
}

void bf_ops_free(BFOps* op_array) {
    free(op_array->ops);
}