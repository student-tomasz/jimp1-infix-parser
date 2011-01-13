#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "expression.h"
#include "token_stack.h"
#include "operator.h"
#include "translator.h"

#define max_token_len 64

static char *var_evaluate(char *variables, char *token);
static int strisnum(char *source);
static int strtoktoa(char *source, const char *delimiters, char ***tokens);


char *expr_evaluate(expr_t *expression, char *variables)
{
    token_stack_t *numbers_stack = NULL;
    
    char *postfix = malloc(sizeof(char) * (strlen(expression->postfix) + 1));
    strcpy(postfix, expression->postfix);
    
    char **tokens = NULL;
    int tokens_count = strtoktoa(postfix, " ", &tokens);
    
    /* iterate over each token in postfix expression */
    int i;
    for (i = 0; i < tokens_count; ++i) {
        char *token = tokens[i];
        /* if 'token' is an operator */
        op_t *op = op_find_by_str(token);
        if (op) {
            char *tmp_str = NULL;
            double a = 0.0, b = 0.0;
            
            /* get first value from numbers stack */
            tmp_str = stack_top(numbers_stack);
            a = atof(tmp_str);
            free(tmp_str);
            stack_pop(&numbers_stack);
            
            /* get second value from numbers stack if operator is binary */
            if (!(op->unary)) {
                tmp_str = stack_top(numbers_stack);
                b = atof(tmp_str);
                free(tmp_str);
                stack_pop(&numbers_stack);
            }
            
            /* put the result on stack */
            tmp_str = malloc(sizeof(char) * (max_token_len + 1));
            snprintf(tmp_str, max_token_len, "%g", (*op->eval)(b, a));
            stack_push(&numbers_stack, tmp_str);
            free(tmp_str);
        }
        /* otherwise replace 'token' with its value from 'variables' */
        else {
            char *new_token = var_evaluate(variables, token);
            if (new_token) {
                stack_push(&numbers_stack, new_token);
                free(new_token);
            }
            else {
                /* TODO: return error message */
                return NULL;
            }
        }
    }
    
    free(tokens);
    free(postfix);
    return stack_top(numbers_stack);
}

expr_t *expr_init(char *name, char *infix)
{
    char *postfix = translate(infix);
    if (!postfix) return 0;

    expr_t *expr = malloc(sizeof(expr_t));
    expr->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(expr->name, name);
    expr->infix = malloc(sizeof(char) * (strlen(infix) + 1));
    strcpy(expr->infix, infix);
    expr->postfix = malloc(sizeof(char) * (strlen(postfix) + 1));
    strcpy(expr->postfix, postfix);

    return expr;
}


static char *var_evaluate(char *variables, char *token)
{
    /* copy variables string so it can be modified */
    char *hash = malloc(sizeof(char) * (strlen(variables) + 1));
    strcpy(hash, variables);
    
    /* divide hash string into pairs */
    char **pairs = 0;
    int pairs_count = strtoktoa(hash, ";", &pairs);
    
    /* iterate over each 'key = value' pair */
    int i;
    for (i = 0; i < pairs_count; ++i) {
        char *pair = pairs[i];
        
        /* divide pair into key 'k' and value 'v' */
        char *eq = strrchr(pair, '=');
        if (!eq) break;
        pair[eq - pair] = '\0';
        char *k = malloc(sizeof(char) * (strlen(pair)+ 1));
        char *v = malloc(sizeof(char) * (strlen(eq + 1) + 1));
        sscanf(pair, "%s", k);
        sscanf(eq+1, "%s", v);
        
        /* if 'token' we're looking for is 'k' */
        if (strcmp(token, k) == 0) {
            free(k);
            free(hash);
            /* then check if 'v' given for this key is a valid number */
            if (strisnum(v)) {
                return v;
            }
            /* else report an error */
            else {
                char *msg = malloc(sizeof(char) * (max_msg_len + 1));
                sprintf(msg, "'%s' is not a proper number", v);
                error(msg);
                
                free(msg);
                free(v);
                return NULL;
            }
        }
        
        /* so, 'token' is not defined in current pair, try another */
        free(v);
        free(k);
    }
    free(hash);
    
    /* there are no matches for our 'token', maybe it's only a number */
    if (strisnum(token)) {
        char *v = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(v, token);
        return v;
    }
    
    /* nah, you're doing it wrong */
    char *msg = malloc(sizeof(char) * (max_msg_len + 1));
    sprintf(msg, "can't find value for '%s' variable", token);
    error(msg);
    
    return 0;
}


static int strisnum(char *source)
{
    char *curr = 0;
    for (curr = source; *curr; ++curr) {
        if (!isdigit(*curr) && *curr != '.' && *curr != '-') {
            return 0;
        }
    }
    return 1;
}

/* string tokenize to array: */
/* similar to strtok,
   tokenizes 'source' by splitting it using characters in 'delimiters' and writes address to each token's beginning into 'tokens' array
   returns number of tokens found */
static int strtoktoa(char *source, const char *delimiters, char ***tokens)
{
    *tokens = malloc(sizeof(char *));
    int tokens_count = 0;

    /* count how many pairs we've got */
    char *curr = source;
    
    (*tokens)[0] = source;
    tokens_count++;
    for (curr = source; *curr; ++curr) {
        if (strchr(delimiters, *curr) != NULL) {
            *tokens = realloc(*tokens, (sizeof(char *) * (++tokens_count)));

            *curr = '\0';
            (*tokens)[tokens_count-1] = curr + 1;
        }
    }

    return tokens_count;
}