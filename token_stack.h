#ifndef _TOKEN_STACK_H
#define _TOKEN_STACK_H

typedef struct token_stack_s {
    char *value;
    struct token_stack_s *next;
} token_stack_t;
// } stack_t;

void stack_push(token_stack_t **head, char *value);
void stack_pop(token_stack_t **head);
char *stack_top(token_stack_t *head);
void stack_print(token_stack_t *head);
int stack_empty(token_stack_t *head);
void stack_free(token_stack_t *head);

#endif /* _TOKEN_STACK_H */
