#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "translator.h"
#include "expression.h"

int tests_run = 0;

int main(int argc, char **argv)
{
    int (*test_suites[])() = {
        all_translator_tests,
        all_expression_tests
    };

    int i;
    for(i = 0; i < (sizeof(test_suites)/sizeof(test_suites[0])); ++i) {
        if ((test_suites[i])()) {
            printf("\nfail: some tests failed\n\n");
            return 1;
        }
    }
    printf("\nsuccess: all %d tests passed\n\n", tests_run);
    return 0;
}
