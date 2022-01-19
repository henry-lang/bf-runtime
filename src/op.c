#include <stdlib.h>

#include "op.h"

void bf_op_array_init(BFOpArray* op_array, size_t capacity) {
    op_array->ops = malloc(sizeof(BFOp) * capacity);
    op_array->length = 0;
    op_array->capacity = capacity;
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