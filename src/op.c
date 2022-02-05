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

BFOpArray bf_op_array_init(size_t capacity) {
    return (BFOpArray) {
        .ops = malloc(sizeof(BFOp) * capacity),
        .length = 0,
        .capacity = capacity
    };
}

void bf_op_array_append(BFOpArray* op_array, BFOp op) {
    if(op_array->length == op_array->capacity) {
        op_array->capacity *= 2;
        op_array->ops = realloc(op_array->ops, op_array->capacity * sizeof(BFOp));
    }
    op_array->ops[op_array->length++] = op;
}

void bf_op_array_free(BFOpArray* op_array) {
    free(op_array->ops);
}