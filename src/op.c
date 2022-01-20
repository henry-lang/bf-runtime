#include <stdlib.h>

#include "op.h"

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