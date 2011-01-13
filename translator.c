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
    int num_c = 0;
    
    char *token = malloc(sizeof(char) * (strlen(infix) + 1));
    strcpy(token, "\0");
    
    op_t *curr_op = NULL;
    op_t dummy_op = { "@", 0, none, 0 };
    op_t *last_op = &dummy_op;
    
    char *curr;
    for (curr = infix; *curr != '\0'; ++curr) {
        /* if we read operator */
        if ((curr_op = op_find(*curr)) != NULL) {
            /* after another operator different then closing bracket (or it's first char of expr) */
            if (last_op && (last_op == &dummy_op || !op_is_equal(last_op, ")"))) {
                /* and it's a '-' */
                if (op_is_equal(curr_op, "-")) {
                    curr_op = op_find('~'); /* then accept '-' operator as an unary minus, it's the only place possible */
                }
                /* it can also be an opening bracket */
                else if (op_is_equal(curr_op, "(")) {
                    ; /* and that's ok with us */
                }
                /* otherwise we've have an operator right after another operator */
                else {
                    char *msg = malloc(sizeof(char) * (max_msg_len + 1));
                    int pos = curr-(infix+1);
                    char *th = (pos == 1 ? "st" : (pos == 2 ? "nd" : "th"));
                    sprintf(msg, "syntax error in infix expression near %d%s character", pos, th);
                    error(msg);
                    
                    free(msg);
                    free(token);
                    free(postfix);
                    return 0;
                }
            }
            
            /* now we have to deal with this operator */
            /* if opening bracket then just put it on stack */
            if (op_is_equal(curr_op, "(")) {
                stack_push(&ops_st, "(");
            }
            /* if closing bracket then pop all operators until matching bracket is found */
            else if (op_is_equal(curr_op, ")")) {
                op_t *tmp_op = op_find_by_str(stack_top(ops_st));
                while (!stack_empty(ops_st) && !op_is_equal(tmp_op, "(")) {
                    strcat(postfix, tmp_op->op); /* add to output */
                    strcat(postfix, " ");
                    if (!(tmp_op->unary)) { /* decrement unused numbers */
                        --num_c;
                    }
                    stack_pop(&ops_st); /* remove from stack */
                    tmp_op = op_find_by_str(stack_top(ops_st)); /* get next operator from stack */
                }
                /* now get rid of '(' from stack */
                /* if stack hit bottom or last op from stack isn't '(' then fail */
                if (stack_empty(ops_st) || !op_is_equal(tmp_op, "(")) {
                    error("unmatched brackets");
                    
                    free(token);
                    free(postfix);
                    return 0;
                }
                /* otherwise pop it from stack and carry on */
                else {
                    stack_pop(&ops_st);
                }
            }
            /* if regular operator then we're fucked */
            else {
                /* pop all operators until we get one is counted after current op */
                while (!stack_empty(ops_st)) {
                    op_t *op1 = curr_op;
                    op_t *op2 = op_find_by_str(stack_top(ops_st));
                    if ((op1->association == left && op1->precedence <= op2->precedence) ||
                        (op1->association == right && op1->precedence < op2->precedence)) {
                            strcat(postfix, op2->op);
                            strcat(postfix, " ");
                            if (!(op2->unary)) { /* decrement unused numbers */
                                --num_c;
                            }
                            stack_pop(&ops_st);
                    }
                    else {
                        break;
                    }
                }
                /* put current op onto the stack */
                stack_push(&ops_st, curr_op->op);
            }
            /* update last_op to the just processed operator */
            last_op = curr_op;
        }
        /* if it's not an operator, but it's a valid number/variable */
        else if (is_operand(*curr)) {
            /* read the whole operand name */
            char *operand_start = curr;
            while ((*curr) && is_operand(*curr)) {
                ++curr;
            }
            strncpy(token, operand_start, curr - operand_start);
            token[curr - operand_start] = '\0';
            strcat(postfix, token);
            strcat(postfix, " ");
            /* go back to the last char of token, for loop will increment curr */
            --curr;
            /* reset occurence of last operator */
            last_op = NULL;
            /* bump up numbers unused in expression */
            ++num_c;
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
    if (!stack_empty(ops_st)) {
        error("umatched brackets");
        
        free(token);
        free(postfix);
        return 0;
    }
    
    /* if there is more than one unused number left (which will be a result) then we'ge got mismatched opartors */
    if (num_c != 1) {
        error("quantity of operators doesn\'t match quantity of operands");
        
        free(token);
        free(postfix);
        return 0;
    }
    
    /* else everything went according to plan, then remove the trailing space and return */
    if (postfix[strlen(postfix)-1] == ' ') {
        postfix[strlen(postfix)-1] = '\0';
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
