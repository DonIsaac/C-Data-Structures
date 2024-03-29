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

/**
 * @brief  A test result returned by failed assertions.
 * 
 * @details Test results are returned in tests by assertions. Assertions check
 * a condition, and return information about the failure such as the file name,
 * and line/column of the failure. When tests pass, they return MU_TEST_PASS.
 * 
 */
struct mu_res {
    const char *file;
    unsigned int line;
    const char *msg;
    const char *assertion;
};

#define MU_TEST_PASS NULL

/**
 * @brief Defines a test function.
 * 
 */
#define mu_test(name) static struct mu_res *name()

/**
 * @brief Asserts that a condition is true and fails the test with the provided
 * message if it is not.
 * 
 */
#define mu_assert(message, test)                 \
    do {                                         \
        num_assertions++;                        \
        if (!(test)) {                           \
            struct mu_res *ret = {0};            \
            ret = malloc(sizeof(struct mu_res)); \
            ret->file = __FILE__;                \
            ret->line = __LINE__;                \
            ret->msg = message;                  \
            ret->assertion = #test;              \
            return ret;                          \
        }                                        \
    } while (0)

/**
 * @brief Fails a test unconditionally.
 * 
 */
#define mu_fail(message) mu_assert(message, 0)

/**
 * @brief Runs a test and prints the result.
 * 
 * @see mu_test
 * 
 */
#define mu_run_test(test)                                                                                 \
    do {                                                                                                  \
        printf("Running %s:\t", #test);                                                                   \
        struct mu_res *ret = test();                                                                      \
        tests_run++;                                                                                      \
        if (ret) {                                                                                        \
            printf("failed\n");                                                                           \
            printf("\n(%s:%u): %s\n\tassertion: %s\n\n", ret->file, ret->line, ret->msg, ret->assertion); \
            tests_failed++;                                                                               \
            /* return ret; */                                                                             \
        } else {                                                                                          \
            printf("passed\n");                                                                           \
        }                                                                                                 \
    } while (0) 

extern int tests_run;
extern int tests_failed;
extern int num_assertions;

#endif
