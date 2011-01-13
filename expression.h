#ifndef _EXPRESSION_H
#define _EXPRESSION_H

typedef struct expr_s {
    char *name;
    char *infix;
    char *postfix;
} expr_t;

char *expr_evaluate(expr_t *expression, char *variables);
expr_t *expr_init(char *name, char *infix);

#endif /* _EXPRESSION_H */
