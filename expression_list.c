#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expression_list.h"
#include "expression.h"

void expr_list_add(expr_list_t **head, expr_t *expr)
{
    expr_list_t *node = malloc(sizeof(expr_list_t));
    node->expr = expr;
    
    node->next = (*head);
    (*head) = node;
}

expr_t *expr_list_find(expr_list_t *head, char *name)
{
    expr_list_t *node = head;
    while (node != NULL) {
        if (strcmp(node->expr->name, name) == 0) {
            return node->expr;
        }
        node = node->next;
    }
    return NULL;
}

void expr_list_print(expr_list_t *head)
{
    expr_list_t *node;
    for (node = head; node != NULL; node = node->next) {
        printf("%s ", node->expr->name);
    }
    printf("\n");
}
