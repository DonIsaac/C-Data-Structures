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
#define mu_assert(message, test)                                               \
  do {                                                                         \
    if (!(test))                                                               \
      return message;                                                          \
  } while (0)

#define mu_run_test(test)                                                      \
  do {                                                                         \
    printf("Running %s: ", #test);                                             \
    char *message = test();                                                    \
    tests_run++;                                                               \
    if (message) {                                                             \
      printf("failed\n");                                                      \
      return message;                                                          \
    } else {                                                                   \
      printf("passed\n");                                                      \
    }                                                                          \
  } while (0)
extern int tests_run;
