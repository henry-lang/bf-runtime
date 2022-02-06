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

typedef struct BFOps {
    BFOp* ops;
    size_t length;
    size_t capacity;
} BFOps;

char* bf_op_str(BFOpType op);

BFOps bf_ops_init(size_t capacity);
void bf_ops_append(BFOps* op_array, BFOp op);
void bf_ops_print(BFOps* op_array);
void bf_ops_free(BFOps* op_array);