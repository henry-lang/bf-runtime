#include <stdint.h>
#include <stdio.h>

#include "log.h"
#include "optimize.h"

BFOpArray bf_optimize(BFOpArray* unoptimized) {
    BFOpArray op_array = bf_op_array_init(unoptimized->length);

    for(int i = 0; i < unoptimized->length; i++) {
        BFOp* current = &op_array.ops[i];
        switch(current->type) {
            default: {
                bf_logf_error("%s%d", "Unexpected instruction: ", current->type);
                break;
            }
            case CHANGE: {
                int64_t value = current->value;
                while(op_array.ops[++i].type == CHANGE && i < op_array.length) {
                    value += op_array.ops[i].value;
                }
                bf_op_array_append(&op_array, (BFOp) {
                    .type = CHANGE,
                    .value = value
                });

                break;
            }
            case MOVE: {
                int64_t value = current->value;
                while(op_array.ops[++i].type == MOVE && i < op_array.length) {
                    value += op_array.ops[i].value;
                }
                bf_op_array_append(&op_array, (BFOp) {
                    .type = MOVE,
                    .value = value
                });

                break;
            }
            case JUMP_ZERO: {
                bf_op_array_append(&op_array, (BFOp) {
                    .type = JUMP_ZERO,
                    .value = 0 // Temporary
                });
                break;
            }
            case JUMP_NONZERO: {
                bf_op_array_append(&op_array, (BFOp) {
                    .type = JUMP_NONZERO,
                    .value = 0 // Temporary
                });
                break;
            }
            case PUT: {
                bf_op_array_append(&op_array, (BFOp) {
                    .type = PUT,
                    .value = 1
                });
                break;
            }
            case GET: {
                bf_op_array_append(&op_array, (BFOp) {
                    .type = GET,
                    .value = 1
                });
                break;
            }
        }
    }

    return op_array;
}