#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token_stack.h"

void stack_push(token_stack_t **head, char *value)
{
    token_stack_t *node = malloc(sizeof(*node));
    
    node->value = malloc(sizeof(*(node->value)) * (strlen(value) + 1));
    strcpy(node->value, value);
    node->next = (*head);
    
    (*head) = node;
}

void stack_pop(token_stack_t **head)
{
    token_stack_t *node = (*head);
    if (!node) {
        fprintf(stderr, "%s:%d: error: stack underflow\n", __FILE__, __LINE__);
        abort();
    }

    (*head) = node->next;
    free(node->value);
    free(node);
}

char *stack_top(token_stack_t *head)
{
    if (head == NULL) {
        return NULL;
    }
    char *value = malloc(sizeof(*(head->value)) * (strlen(head->value) + 1));
    strcpy(value, head->value);
    return value;
}

void stack_print(token_stack_t *head)
{
    token_stack_t *node = head;
    while (node) {
        fprintf(stdout, "%s ", node->value);
        node = node->next;
    }
    fprintf(stdout, "\n");
}

int stack_is_empty(token_stack_t *head) /* yeah, I know... */
{
    return head == NULL;
}

void stack_free(token_stack_t *head)
{
    token_stack_t *node;
    while (head) {
        node = head;
        head = node->next;
        free(node->value);
        free(node);
    }
}
