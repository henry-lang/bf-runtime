#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef enum BFOpType {
    BF_OP_INC, // Increment
    BF_OP_DEC, // Decrement
    BF_OP_FW,  // Forward
    BF_OP_BK,  // Backward
    BF_OP_SZ,  // Set Zero
    BF_OP_JZ,  // Jump If Zero
    BF_OP_JNZ, // Jump If Not Zero
    BF_OP_PUT, // Put Cell
    BF_OP_GET  // Get Into Cell
} BFOpType;

typedef struct BFOp {
    BFOpType type;
    size_t value;
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
