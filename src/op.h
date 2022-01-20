#include <stdint.h>
#include <stdlib.h>

#ifndef BF_OP_H
#define BF_OP_H

typedef enum BFOpType {
    CHANGE,       // intmax_t
    MOVE,         // intmax_t
    SET_ZERO,     // N/A
    JUMP_ZERO,    // uintmax_t
    JUMP_NONZERO, // uintmax_t
    PUT,          // N/A
    GET           // N/A
} BFOpType;

typedef struct BFOp {
    BFOpType type;
    union {
        intmax_t int_val;
        uintmax_t uint_val;
    } value;
} BFOp;

typedef struct BFOpArray {
    BFOp* ops;
    size_t length;
    size_t capacity;
} BFOpArray;

BFOpArray bf_op_array_init(size_t capacity);
void bf_op_array_append(BFOpArray* op_array, BFOp op);
void bf_op_array_free(BFOpArray* op_array);

#endif
