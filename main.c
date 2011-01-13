#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expression.h"
#include "expression_list.h"

#define MAX_CMD_LEN 1024

static void expr_define(expr_list_t **expressions);
static void expr_calculate(expr_list_t *expressions);
static void getstr(char *dest);


int main(int argc, char const **argv)
{
    expr_list_t *expressions = NULL;
    
    printf("there 3 options:\n");
    printf("* \"def\"  - to define an expression\n");
    printf("* \"cal\"  - to evaluate one\n");
    printf("* \"exit\" - to exit\n");
    
    char cmd[MAX_CMD_LEN + 1];
    do {
        printf("\n---\n");
        printf("? ");
        getstr(cmd);
        printf("\n");
        if (strcmp(cmd, "def") == 0 || strcmp(cmd, "d") == 0) {
            expr_define(&expressions);
        }
        else if (strcmp(cmd, "cal") == 0 || strcmp(cmd, "c") == 0) {
            expr_calculate(expressions);
        }
        else if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "x") == 0) {
            break;
        }
        else if (strcmp(cmd, "p") == 0) {
            expr_list_print(expressions);
        }
        else {
            continue;
        }
    } while (1);

    return 0;
}


static void expr_define(expr_list_t **expressions)
{
    char *name = malloc(sizeof(char) * (MAX_CMD_LEN + 1));
    char *infix = malloc(sizeof(char) * (MAX_CMD_LEN + 1));
    
    printf("define new expression:\n");
    printf("* name: ");
    getstr(name);
    printf("* expression: ");
    getstr(infix);
    printf("\n");
    
    expr_t *expression = expr_init(name, infix);
    if (!expression) {
        printf("'%s' is not a valid expression\n", infix);
        free(infix);
        free(name);
        return;
    }
    expr_list_add(expressions, expression);
    
    printf("just created expression:\n");
    printf("* name    : '%s'\n", expression->name);
    printf("* infix   : '%s'\n", expression->infix);
    printf("* postfix : '%s'\n", expression->postfix);
    
    free(infix);
    free(name);
}

static void expr_calculate(expr_list_t *expressions)
{
    char *name = malloc(sizeof(char) * (MAX_CMD_LEN + 1));
    char *variables = malloc(sizeof(char) * (MAX_CMD_LEN + 1));
    expr_t *expression = NULL;
    
    printf("evaluate expression from the list below:\n");
    printf("# ");
    expr_list_print(expressions);
    printf("* name: ");
    getstr(name);
    
    if ((expression = expr_list_find(expressions, name)) == NULL) {
        printf("there is no '%s' expression\n", name);
        free(variables);
        free(name);
        return;
    }
    else {
        printf("# %s\n", expression->infix);
    }
    
    printf("* variables: ");
    getstr(variables);
    
    char *result = expr_evaluate(expression, variables);
    if (result) {
         printf("result = %s\n", result);
         free(result);
    }
    free(variables);
    free(name);
}

static void getstr(char *dest)
{
    if (fgets(dest, MAX_CMD_LEN, stdin)) {
        (*strchr(dest, '\n')) = '\0';
    }
    else {
        strcpy(dest, "\0");
    }
}
