/* http://www.jera.com/techinfo/jtns/jtn002.html */

#ifndef _MINUNIT_H
#define _MINUNIT_H

#define mu_assert(assertion) do { ++tests_run; if (!(assertion)) { printf("%s:%d: fail: %s\n", __FILE__, __LINE__, __func__); return 1; } } while (0)
#define mu_run_test(test) do { int msg = test(); if (msg) return 1; } while (0)

extern int tests_run;

#define streql(left, right) (strcmp(left, right) == 0)

#endif /* _MINUNIT_H */
