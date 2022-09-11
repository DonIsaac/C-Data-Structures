#include "minunit.h"
#include <stdlib.h>

#include "../src/lib/geometry.h"
#include "../src/lib/epsilon.h"
#include "math.h"

int tests_failed = 0;
int tests_run = 0;
int num_assertions = 0;

pointd_t zero = {0.0, 0.0};
pointd_t one = {1.0, 1.0};

mu_test(test_geom_point_eq) {
    pointd_t p1 = {5.24, 3.14};
    pointd_t p2 = {5.24, 3.14};

    // Check equal
    mu_assert("(0, 0) == (0, 0)", pointd_eq(zero, zero));
    mu_assert("(1, 1) == (1, 1)", pointd_eq(one, one));
    mu_assert("(5.24, 3.14) == (5.24, 3.14)",  pointd_eq(p1, p2));

    // Check not equal
    mu_assert("(0, 0) != (1, 1)", !pointd_eq(zero, one));
    mu_assert("(1, 1) != (0, 0)", !pointd_eq(one, zero));
    mu_assert("(5.24, 3.14) != (0, 0)", !pointd_eq(p1, zero));

    return MU_TEST_PASS;
}

mu_test(test_geom_point_dist) {
    mu_assert("Distance between (0, 0) and (0, 0) is 0", pointd_dist(zero, zero) == 0.0);
    mu_assert("Distance between (1, 1) and (1, 1) is 0", pointd_dist(one, one) == 0.0);

    mu_assert("Distance between (0, 0) and (1, 1) is sqrt(2)", cmp_d(pointd_dist(zero, one), sqrt(2.0)) == 0);

    return MU_TEST_PASS;
}

mu_test(test_geom_point_distm) {
    mu_assert("Manhattan distance between (0, 0) and (0, 0) is 0", pointd_distm(zero, zero) == 0.0);
    mu_assert("Manhattan distance between (0, 0) and (1, 1) is 2", pointd_distm(zero, one) == 2.0);
    mu_assert("Manhattan distance between (0, 0) and (-5, 0) is 5", pointd_distm(zero, (pointd_t){-5.0, 0.0}) == 5.0);
    mu_assert("Mahattan distance between (0, 0) and (1, -1) is 2", pointd_distm(zero, (pointd_t){1.0, -1.0}) == 2.0);

    return MU_TEST_PASS;
}

void all_tests() {
    mu_run_test(test_geom_point_eq);
    mu_run_test(test_geom_point_dist);
    mu_run_test(test_geom_point_distm);
}

int main() {
    // struct mu_res *result = all_tests();
    all_tests();

    printf("\nTests run: %d\nTests failed: %d\nTotal assertions: %d\n\n", tests_run, tests_failed, num_assertions);

    if (!tests_failed) {
        printf("All tests passed\n");
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
