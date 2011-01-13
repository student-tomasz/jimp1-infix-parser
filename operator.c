#include <stdlib.h>
#include <string.h>
#include "operator.h"

op_t valid_ops[] = {
    { "~", 99, right, 1 }, /* different operator for unary minus */
    { "*", 2, left, 0 },
    { "/", 2, left, 0 },
    { "+", 1, left, 0 },
    { "-", 1, left, 0 },
    { "(", 0, none, 0 },
    { ")", 0, none, 0 }
};

op_t *op_find(char c)
{
    op_t *op = NULL;
    int i;
    for (i = 0; i < (sizeof(valid_ops)/sizeof(valid_ops[0])); ++i) {
        op = valid_ops + i;
        if (op->op[0] == c) {
            return op;
        }
    }
    return NULL;
}

op_t *op_find_by_str(char *c)
{
    if (!c) return 0;
    
    op_t *op = NULL;
    int i;
    for (i = 0; i < (sizeof(valid_ops)/sizeof(valid_ops[0])); ++i) {
        op = valid_ops + i;
        if (op_is_equal(op, c)) {
            return op;
        }
    }
    return NULL;
}

int op_is_equal(op_t *op, char *str)
{
    if (!op || !str)
        return 0;
    return strcmp(op->op, str) == 0;
}