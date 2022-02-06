#include <stdint.h>
#include <stdio.h>

#include "log.h"
#include "optimize.h"

BFOps bf_optimize(BFOps* unopt) {
    BFOps op_array = bf_ops_init(64);

    for(int i = 0; i < unopt->length; i++) {
        BFOp* current = &unopt->ops[i];
        switch(current->type) {
            default: {
                bf_logf_error("%s%d", "Unexpected instruction: ", current->type);
                break;
            }
            case CHANGE: {
                int64_t value = current->value;
                while(i < unopt->length && unopt->ops[i + 1].type == CHANGE) {
                    i++;
                    value += unopt->ops[i].value;
                }
                bf_ops_append(&op_array, (BFOp) {
                    .type = CHANGE,
                    .value = value
                });

                break;
            }
            case MOVE: {
                int64_t value = current->value;
                while(i < unopt->length && unopt->ops[i + 1].type == MOVE) {
                    i++;
                    value += unopt->ops[i].value;
                }
                bf_ops_append(&op_array, (BFOp) {
                    .type = MOVE,
                    .value = value
                });

                break;
            }
            case JUMP_ZERO: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = JUMP_ZERO,
                    .value = 0 // Temporary
                });
                break;
            }
            case JUMP_NONZERO: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = JUMP_NONZERO,
                    .value = 0 // Temporary
                });
                break;
            }
            case PUT: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = PUT,
                    .value = 1
                });
                break;
            }
            case GET: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = GET,
                    .value = 1
                });
                break;
            }
        }
    }
    return op_array;
}