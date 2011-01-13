#include <stdlib.h>
#include "operator.h"

op_t valid_ops[] = {
    { '~', 99, right, 1 }, /* different operator for unary minus */
    { '*', 2, left, 0 },
    { '/', 2, left, 0 },
    { '+', 1, left, 0 },
    { '-', 1, left, 0 },
    { '(', 0, none, 0 },
    { ')', 0, none, 0 }
};

op_t *find_op(char c)
{
    op_t *op = NULL;
    int i;
    for (i = 0; i < (sizeof(valid_ops)/sizeof(valid_ops[0])); ++i) {
        op = valid_ops + i;
        if (op->op == c) {
            return op;
        }
    }
    return NULL;
}
