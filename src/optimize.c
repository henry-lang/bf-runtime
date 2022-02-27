#include <stdint.h>
#include <stdio.h>

#include "parse.h"
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
                bf_ops_append(&op_array, (BFOp) {
                    .type = current->type,
                    .value = current->value
                });
                break;
            }
            REPEATING_OP(BF_OP_INC);
            REPEATING_OP(BF_OP_DEC);
	        REPEATING_OP(BF_OP_FW);
	        REPEATING_OP(BF_OP_BK);
            case BF_OP_JZ: {
                // Set Zero Optimization
                if(i < unopt->length - 2 &&
                    unopt->ops[i + 1].type == BF_OP_DEC &&
                    unopt->ops[i + 2].type == BF_OP_JNZ) {
                    i += 2;
                    bf_ops_append(&op_array, (BFOp) {
                        .type = BF_OP_SZ,
                        .value = 0
                    });
                } else {
                    bf_ops_append(&op_array, (BFOp) {
                        .type = BF_OP_JZ,
                        .value = 0 
                    });
                }
                break;
            }
        }
    }

    bf_link(&op_array);

    return op_array;
}
