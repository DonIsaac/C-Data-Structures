#include "minunit.h"

#include <string.h>

#include "../src/map/quadtree.h"

int tests_failed = 0;
int tests_run = 0;
int num_assertions = 0;

mu_test(test_qt_simple_add) {
    QuadTree *tree = NULL;
    map_status_t status;

    status = qt_init(&tree);
    mu_assert("QuadTree init should be successful", status == _MAP_SUCCESS);
    mu_assert("QuadTree should not be null after initialization", tree != NULL);
    mu_assert("QuadTree should have a size of 0 after initialization", qt_size(tree) == 0);

    qt_key_t key = { 0.0, 0.0 };
    char *data = "Hello, world!";
    status = qt_add(tree, key, data, strlen(data));
    mu_assert("QuadTree add should be successful", status == _MAP_SUCCESS);
    mu_assert("QuadTree should have a size of 1 after adding an element", qt_size(tree) == 1);

    char* result = qt_get(tree, key);
    mu_assert("qt_get should not return null when retrieving a stored key", result != NULL);
    mu_assert("qt_get should return the same data that was stored", strcmp(data, result) == 0);

    return MU_TEST_PASS;
}

void all_tests() {
    mu_run_test(test_qt_simple_add);
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
