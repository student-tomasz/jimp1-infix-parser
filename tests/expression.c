#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "../main.h"
#include "../expression.h"

static int failing_suite()
{
    expr_t *expr_a = expr_init("expr_a", "((a+b)/c*-d)");
    
    mu_assert(!expr_evaluate(expr_a, ""));
    mu_assert(!expr_evaluate(expr_a, "  "));
    mu_assert(!expr_evaluate(expr_a, " ; ;"));
    mu_assert(!expr_evaluate(expr_a, ";;"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b;"));
    mu_assert(!expr_evaluate(expr_a, ";a=3;;"));
    mu_assert(!expr_evaluate(expr_a, ";;;a3  ;b=;"));
    mu_assert(!expr_evaluate(expr_a, ";;===;a3  ;b=;"));
    mu_assert(!expr_evaluate(expr_a, ";a=3;;c=d;"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b = 1;d = notanumber; c = 4"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b =;d = 3 c = 4"));
    mu_assert(!expr_evaluate(expr_a, "a=-;b =3;d = 3; c = 4"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b=.;d=3;c=4"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b=3;d=3;c=4..1"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b=--3;d=3;c=4"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b= - -3;d=3;c=4"));
    mu_assert(!expr_evaluate(expr_a, "a=.3.4;b=3;d=3;c=4"));
    mu_assert(!expr_evaluate(expr_a, "a=-.3.4;b=3;d=3;c=4"));
    mu_assert(!expr_evaluate(expr_a, "a=--3.4;b=3;d=3;c=4"));
    mu_assert(!expr_evaluate(expr_a, "a=3;b=3;d= ..3;c=4"));
    mu_assert(!expr_evaluate(expr_a, "a=3.3;b=-3.4.;d=3;c=4"));
    return 0;
}

static int passing_suite()
{
    expr_t *expr_a = expr_init("expr_a", "((a+b)/c*-d)");
    
    // mu_assert(streql(expr_evaluate(expr_a, ""), ""));
    mu_assert(streql(expr_evaluate(expr_a, "a=3;b=2;c=5;d=6"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "a = 3;b= 2;c=  -5;d\t=-6.0"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "a=3;b=2;c=5;d=6;"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "a = 3;  b= 2; c  =5;\td\t=6"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "a=3;b=2;c=5;\td asd=6;"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "+=3;a=3;b=2;c=5;\td asd=6;"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "(a+)=5;a=3;b=2;c=5;\td asd=6;"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "a=4.2;b=.8;c=5;d=6;"), "-6"));
    mu_assert(streql(expr_evaluate(expr_a, "a=-4.2;b=-.8;c=5;d=6;"), "6"));
    return 0;
}


int all_expression_tests()
{
    int (*tests[])() = {
        failing_suite,
        passing_suite
    };
    
    int i;
    for (i = 0; i < (sizeof(tests)/sizeof(tests[0])); ++i) {
        mu_run_test(tests[i]);
    }
    return 0;
}