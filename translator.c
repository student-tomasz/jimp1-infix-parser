#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "token_stack.h"
#include "operator.h"


static char *wrap_in_brackets(char *expr);


char *translate(char *infix)
{
    infix = wrap_in_brackets(infix);
    
    char *postfix = malloc(sizeof(char) * (strlen(infix) * 2 + 1));
    strcpy(postfix, "\0");
    
    token_stack_t *ops_st = NULL;
    
    char *token = malloc(sizeof(char) * (strlen(infix) + 1));
    strcpy(token, "\0");
    char *token_start = NULL;
    
    op_t *curr_op = NULL;
    op_t dummy_op = { '@', 0, none, 0 };
    op_t *last_op = &dummy_op;
    
    char *curr;
    for (curr = infix; *curr != '\0'; ++curr) {
        /* if we read operator */
        if ((curr_op = find_op(*curr)) != NULL) {
            /* after another operator different then closing bracket (or it's first char of expr) */
            if (last_op && (last_op == &dummy_op || last_op->op != ')')) {
                /* and it's a '-' */
                if (curr_op->op == '-') {
                    curr_op = find_op('~'); /* then accept '-' operator as an unary minus, it's the only place possible */
                }
                /* it can also be an opening bracket */
                else if (curr_op->op == '(') {
                    ; /* and that's ok with us */
                }
                /* otherwise we've have an operator right after another operator */
                else {
                    char *msg = malloc(sizeof(char) * (max_msg_len + 1));
                    char *th = NULL;
                    int pos = curr-(infix+1);
                    th = (pos == 1 ? "st" : (pos == 2 ? "nd" : "th"));
                    sprintf(msg, "syntax error near %ld%s character", pos, th);
                    error(msg);
                    
                    free(msg);
                    free(token);
                    free(postfix);
                    return 0;
                }
            }
            
            /* now we have to deal with this operator */
            /* if opening bracket then just put it on stack */
            if (curr_op->op == '(') {
                stack_push(&ops_st, "(");
            }
            /* if closing bracket then pop all operators until matching bracket is found */
            else if (curr_op->op == ')') {
                char *stacked_op = NULL;
                while (!stack_empty(ops_st) && !streql(stacked_op = stack_top(ops_st), "(")) {
                    strcat(postfix, stacked_op); /* add to output */
                    strcat(postfix, " ");
                    stack_pop(&ops_st); /* remove from stack */
                    free(stacked_op);
                }
                /* now get rid of '(' from stack */
                /* if stack hit bottom or last op from stack isn't '(' then fail */
                if (stack_empty(ops_st) || !streql(stacked_op, "(")) {
                    error("unmatched brackets");
                    
                    free(token);
                    free(postfix);
                    return 0;
                }
                /* otherwise pop it from stack and carry on */
                else {
                    stack_pop(&ops_st);
                    free(stacked_op);
                }
            }
            /* if regular operator then we're fucked */
            else {
                /* pop all operators until we get one is counted after current op */
                while (!stack_empty(ops_st)) {
                    char *stacked_op = stack_top(ops_st);
                    op_t *op1 = curr_op;
                    op_t *op2 = find_op(stacked_op[0]);
                    if ((op1->association == left && op1->precedence <= op2->precedence) ||
                        (op1->association == right && op1->precedence < op2->precedence)) {
                            stack_pop(&ops_st);
                            strcat(postfix, stacked_op);
                            strcat(postfix, " ");
                    }
                    else {
                        free(stacked_op);
                        break;
                    }
                    free(stacked_op);
                }
                /* put current op onto the stack */
                char *stacked_op = malloc(sizeof(char) * (2 + 1));
                sprintf(stacked_op, "%c", curr_op->op);
                stack_push(&ops_st, stacked_op);
                free(stacked_op);
            }
            /* update last_op to the just processed operator */
            last_op = curr_op;
        }
        /* if it's not an operator, but it's a valid number/variable */
        else if (is_operand(*curr)) {
            /* read the whole operand name */
            token_start = curr;
            while ((*curr) && is_operand(*curr)) {
                ++curr;
            }
            strncpy(token, token_start, curr-token_start);
            token[curr-token_start] = '\0';
            strcat(postfix, token);
            strcat(postfix, " ");
            /* go back to the last char of token, for loop will increment curr */
            --curr;
            /* reset occurence of last operator */
            last_op = NULL;
        }
        /* or we can stumble upon smth totally different */
        else if (!is_whitespace(*curr)) {
            char *msg = malloc(sizeof(char) * (max_msg_len +1));
            sprintf(msg, "unknown character \'%c\' in expression", *curr);
            error(msg);
            
            free(msg);
            free(token);
            free(postfix);
            return 0;
        }
    }
    
    /* if there is anything left on stack, then we have unmatched brackets */
    while (!stack_empty(ops_st)) {
        error("umatched brackets");
        
        free(token);
        free(postfix);
        return 0;
    }
    
    free(token);
    return postfix;
}


static char *wrap_in_brackets(char *expr)
{
    char *wrapped_expr = malloc(sizeof(char) * (strlen(expr) + 2 + 1));
    sprintf(wrapped_expr, "(%s)", expr);
    return wrapped_expr;
}