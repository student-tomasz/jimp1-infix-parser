#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "operator.h"

op_t valid_ops[] = {
    { "~", 99, right, 1, &negate }, /* different operator for unary minus */
    { "*", 2, left, 0, &multiply },
    { "/", 2, left, 0, &divide },
    { "+", 1, left, 0, &add },
    { "-", 1, left, 0, &subtract },
    { "(", 0, none, 0, 0 },
    { ")", 0, none, 0, 0 }
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

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    if (b <= 1e-13) error("dividing by 0.0");
    return a/b;
}

double negate(double a, double b)
{
    return -b;
}
