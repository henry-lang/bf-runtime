#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef enum BFOpType {
    CHANGE,
    MOVE,
    SET_ZERO,
    JUMP_ZERO,
    JUMP_NONZERO,
    PUT,
    GET
} BFOpType;

typedef struct BFOp {
    BFOpType type;
    int64_t value;
} BFOp;

typedef struct BFOpArray {
    BFOp* ops;
    size_t length;
    size_t capacity;
} BFOpArray;

char* bf_op_str(BFOpType op);

BFOpArray bf_op_array_init(size_t capacity);
void bf_op_array_append(BFOpArray* op_array, BFOp op);
void bf_op_array_free(BFOpArray* op_array);