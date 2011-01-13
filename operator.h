#ifndef _OPERATOR_H
#define _OPERATOR_H

enum operators_association {
    none = 0,
    left,
    right
};

typedef struct op_s {
    char op;
    int precedence;
    int association;
    int unary;
} op_t;

op_t *find_op(char c);

#endif /* _OPERATOR_H */
