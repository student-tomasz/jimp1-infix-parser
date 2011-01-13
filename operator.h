#ifndef _OPERATOR_H
#define _OPERATOR_H

enum operators_association {
    none = 0,
    left,
    right
};

typedef struct op_s {
    char *op;
    int precedence;
    int association;
    int unary;
    double (*eval)(double a, double b);
} op_t;

op_t *op_find(char c);
op_t *op_find_by_str(char *c);
int op_is_equal(op_t *op, char *str);

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double negate(double a, double b);

#endif /* _OPERATOR_H */
