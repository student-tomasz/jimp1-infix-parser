#ifndef _EXPRESSION_LIST_H
#define _EXPRESSION_LIST_H

#include "expression.h"

typedef struct expr_list_s {
    expr_t *expr;
    struct expr_list_s *next;
} expr_list_t;

void expr_list_add(expr_list_t **head, expr_t *expr);
expr_t *expr_list_find(expr_list_t *head, char *name);
void expr_list_print(expr_list_t *head);

#endif /* _EXPRESSION_LIST_H */
