/**
 * @file minunit.h
 *
 * @brief A minimal unit testing framework for C.
 *
 * This is a modified version of minunit.
 *
 * Derived from: https://jera.com/techinfo/jtns/jtn002
 *
 * @author Jera Design LLC
 * @version 1.0.0
 * @date 2021-09-23
 */
#ifndef __MINUNIT_H__
#define __MINUNIT_H__
#include <stdio.h>

#define mu_assert(message, test) \
    do {                         \
        if (!(test))             \
            return message;      \
    } while (0)

#define mu_run_test(test)                                           \
    do {                                                            \
        printf("Running %s:\t", #test);                             \
        char *ret = test();                                         \
        tests_run++;                                                \
        if (ret) {                                                  \
            char msg[512] = {0};                                    \
            printf("failed\n");                                     \
            sprintf(msg, "(%s:%d): %s\n", __FILE__, __LINE__, ret); \
            return ret;                                             \
        } else {                                                    \
            printf("passed\n");                                     \
        }                                                           \
    } while (0)
extern int tests_run;

#endif
