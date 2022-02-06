#include <stdint.h>
#include <stdio.h>

#include "log.h"
#include "optimize.h"

#define REPEATING_OP(OP) \
case OP: { \
    uint16_t value = current->value; \
    while(i < unopt->length && unopt->ops[i + 1].type == OP) { \
        i++; \
        value += unopt->ops[i].value; \
    } \
    bf_ops_append(&op_array, (BFOp) { \
        .type = OP, \
        .value = value \
    }); \
    break; \
}

BFOps bf_optimize(BFOps* unopt) {
    BFOps op_array = bf_ops_init(64);

    for(int i = 0; i < unopt->length; i++) {
        BFOp* current = &unopt->ops[i];
        switch(current->type) {
            default: {
                bf_logf_error("%s%d", "Unexpected instruction: ", current->type);
                break;
            }
	    REPEATING_OP(BF_OP_INC);
	    REPEATING_OP(BF_OP_DEC);
	    REPEATING_OP(BF_OP_FW);
	    REPEATING_OP(BF_OP_BK);
            case BF_OP_JZ: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = BF_OP_JZ,
                    .value = 0 // Temporary
                });
                break;
            }
            case BF_OP_JNZ: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = BF_OP_JNZ,
                    .value = 0 // Temporary
                });
                break;
            }
            case BF_OP_PUT: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = BF_OP_PUT,
                    .value = 1
                });
                break;
            }
            case BF_OP_GET: {
                bf_ops_append(&op_array, (BFOp) {
                    .type = BF_OP_GET,
                    .value = 1
                });
                break;
            }
        }
    }
    return op_array;
}
