#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "../main.h"
#include "../translator.h"

static int empty_and_whitespace()
{
    char *samples[] = { "", "\0", "\n", "     "};
    
    int i;
    for (i = 0; i < (sizeof(samples)/sizeof(samples[0])); ++i) {
        mu_assert(!translate(samples[i]));
    }
    
    return 0;
}

static int only_int()
{
    mu_assert(streql(translate("3"), "3"));
    return 0;
}

static int only_dec()
{
    mu_assert(streql(translate("0.3333"), "0.3333"));
    return 0;
}

static int only_var()
{
    mu_assert(streql(translate("asd"), "asd"));
    return 0;
}

static int un_min_dec()
{
    mu_assert(streql(translate("-3.5"), "3.5 ~"));
    return 0;
}

static int un_min_var()
{
    mu_assert(streql(translate("-q"), "q ~"));
    return 0;
}

static int simple_exp()
{
    mu_assert(streql(translate(" 3- 35.5"), "3 35.5 -"));
    return 0;
}

static int simple_exp_vars()
{
    mu_assert(streql(translate(" a+ -b"), "a b ~ +"));
    return 0;
}

static int expr_mix()
{
    mu_assert(streql(translate("3.5+123-0.5432*-qwe"), "3.5 123 + 0.5432 qwe ~ * -"));
    return 0;
}

static int expr_mix_same_order()
{
    mu_assert(streql(translate("3.5+123-(0.5432*-qwe)"), "3.5 123 + 0.5432 qwe ~ * -"));
    return 0;
}

static int expr_mix_changed_order()
{
    mu_assert(streql(translate("3.5+(123-0.5432)*-qwe"), "3.5 123 0.5432 - qwe ~ * +"));
    return 0;
}

static int uminus_dec()
{
    mu_assert(streql(translate("--3.5"), "3.5 ~ ~"));
    return 0;
}

static int uminus_dec_brackets()
{
    mu_assert(streql(translate("-(-3.5)"), "3.5 ~ ~"));
    return 0;
}

static int uminus_expr_brackets()
{
    mu_assert(streql(translate("-(-9)-3.5"), "9 ~ ~ 3.5 -"));
    return 0;
}

static int uminus_expr_changed_order()
{
    mu_assert(streql(translate("-(-9-3.5)"), "9 ~ 3.5 - ~"));
    return 0;
}

static int brackets_order()
{
    mu_assert(streql(translate("((a+b)/c *( -d))"), "a b + c / d ~ *"));
    return 0;
}

static int brackets_order_more()
{
    mu_assert(streql(translate("((a+t)*((b+(a+c))/(c+d)))"), "a t + b a c + + c d + / *"));
    return 0;
}

static int invalid_expressions()
{
    char *samples[] = {
        "+", "-", "~", "(     )", "()", "())", "(-)", "(+)", "-(*)", ")",
        "(a*", "a +    ", "12.3-", "a+qwe/", "-(9-)3.5",
        "13123 123 + 4", "13123 123 + -4"
    };

    int i;
    for (i = 0; i < (sizeof(samples)/sizeof(samples[0])); ++i) {
        mu_assert(!translate(samples[i]));
    }
    
    return 0;
}


int all_translator_tests()
{
    int (*tests[])() = {
        empty_and_whitespace,
        only_int,
        only_dec,
        only_var,
        un_min_dec,
        un_min_var,
        simple_exp,
        simple_exp_vars,
        expr_mix,
        expr_mix_same_order,
        expr_mix_changed_order,
        uminus_dec,
        uminus_dec_brackets,
        uminus_expr_brackets,
        uminus_expr_changed_order,
        brackets_order,
        brackets_order_more,
        invalid_expressions
    };
    
    int i;
    for (i = 0; i < (sizeof(tests)/sizeof(tests[0])); ++i) {
        mu_run_test(tests[i]);
    }
    return 0;
}