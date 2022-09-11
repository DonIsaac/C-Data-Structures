#include "../src/map/quadtree.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "minunit.h"
#include "util.h"

#define MAX_STRLEN 256

int tests_failed = 0;
int tests_run = 0;
int num_assertions = 0;

mu_test(test_qt_empty) {
    QuadTree *tree = NULL;
    map_status_t status;

    status = qt_init(&tree);
    mu_assert("QuadTree init should be successful", status == _MAP_SUCCESS);
    mu_assert("QuadTree should not be null after initialization", tree != NULL);
    mu_assert("QuadTree should have a size of 0 after initialization", qt_size(tree) == 0);

    qt_key_t key = {0, 0};
    mu_assert("qt_get should return NULL for an empty tree", qt_get(tree, key) == NULL);
    mu_assert("qt_has should return 0 for an empty tree", qt_has(tree, key) == 0);

    qt_free(&tree);
    return MU_TEST_PASS;
}

mu_test(test_qt_simple_add) {
    QuadTree *tree = NULL;
    map_status_t status;

    status = qt_init(&tree);
    mu_assert("QuadTree init should be successful", status == _MAP_SUCCESS);
    mu_assert("QuadTree should not be null after initialization", tree != NULL);
    mu_assert("QuadTree should have a size of 0 after initialization", qt_size(tree) == 0);

    qt_key_t key = {0.0, 0.0};
    char *data = "Hello, world!";
    status = qt_add(tree, key, data, strlen(data));
    mu_assert("QuadTree add should be successful", status == _MAP_SUCCESS);
    mu_assert("QuadTree should have a size of 1 after adding an element", qt_size(tree) == 1);

    char *result = qt_get(tree, key);
    mu_assert("qt_get should not return null when retrieving a stored key", result != NULL);
    mu_assert("qt_get should return the same data that was stored", strcmp(data, result) == 0);

    qt_free(&tree);
    return MU_TEST_PASS;
}

#define TEST_QT_INSERT_FEW_CLEANUP \
    do {\
    qt_free(&tree); \
    for (size_t i = 0; i < num_entries; i++) { \
        if (data[i] != NULL) { \
            free(data[i]); \
        } \
    } \
    } while (0) \

mu_test(test_qt_insert_few) {
    QuadTree *tree = NULL;

    char msg[MAX_STRLEN] = {0};

    const size_t num_entries = 10;
    qt_key_t keys[num_entries];
    char *data[num_entries];

    for (size_t i = 0; i < num_entries; i++) data[i] = NULL;

    /* memset(msg, 0, msglen); */

    for (size_t i = 0; i < num_entries; i++) {
        keys[i].x = (double)i;
        keys[i].y = (double)i;
        data[i] = malloc(MAX_STRLEN);
        memset(data[i], 0, MAX_STRLEN);
        snprintf(data[i], MAX_STRLEN, "Hello, %lu!", i);
    }

    qt_init(&tree);
    for (size_t i = 0; i < num_entries; i++) {
        qt_add(tree, keys[i], data[i], strlen(data[i]));
    }

    // Check tree size after insertion
    size_t tree_size = (size_t)qt_size(tree);
    if (tree_size != num_entries) {
        snprintf(msg, MAX_STRLEN, "Incorrect tree size; Expected %lu, got %lu", num_entries, tree_size);
        /* goto test_qt_insert_few_fail; */
        TEST_QT_INSERT_FEW_CLEANUP;
        mu_fail(msg);
    }

    // Check that all keys are present
    for (size_t i = 0; i < num_entries; i++) {
        qt_key_t key = keys[i];
        char *expected_result = data[i];

        // Check that the tree has the key
        if (!qt_has(tree, key)) {
            snprintf(msg, MAX_STRLEN, "qt_has should return 1 for key (%f, %f)", key.x, key.y);
            TEST_QT_INSERT_FEW_CLEANUP;
            mu_fail(msg);
        }

        // Retrieve the value for the key, and check that it matches the expected result
        char *result = qt_get(tree, key);
        if (result == NULL) {
            snprintf(msg, MAX_STRLEN, "qt_get returned NULL for key (%f, %f)", key.x, key.y);
            TEST_QT_INSERT_FEW_CLEANUP;
            mu_fail(msg);
        }

        if (strcmp(result, expected_result) != 0) {
            snprintf(msg, MAX_STRLEN, "qt_get returned incorrect result for key (%f, %f)", key.x, key.y);
            TEST_QT_INSERT_FEW_CLEANUP;
            mu_fail(msg);
        }
    }

    TEST_QT_INSERT_FEW_CLEANUP;
    return MU_TEST_PASS;

/* test_qt_insert_few_fail: */
    /* qt_free(&tree); */
    /* for (size_t i = 0; i < num_entries; i++) { */
        /* if (data[i] != NULL) { */
            /* free(data[i]); */
        /* } */
    /* } */
    /* mu_fail(msg); */
}

mu_test(test_qt_insert_many) {
    unsigned int seed = 4294967291; // Largest 32-bit prime
    uint32_t num_elements = 10000; // Number of keys to insert. 10k.
    QuadTree *tree = NULL;
    int status = 0; // return status
    int data = 5; // Data being inserted. All elements have the same data for simplicity

    qt_key_t *keys = malloc(sizeof(qt_key_t) * num_elements);
    if (keys == NULL) {
        mu_fail("Failed to allocate memory for keys");
    }

    // Initialize the tree
    status = qt_init(&tree);
    if (status != _MAP_SUCCESS) {
        free(keys);
        mu_fail("QuadTree init should be successful");
    }

    // Set random seed
    srand(seed);

    // Generate random keys
    for (unsigned int i = 0; i < num_elements; i++) {
        qt_key_t *key = &keys[i];
        key->x = drandom_r(&seed);
        key->y = drandom_r(&seed);
        qt_add(tree, *key, &data, sizeof(data));
    }

    // Check size
    if ((uint32_t)qt_size(tree) != num_elements) {
        free(keys);
        free(tree);
        mu_fail("QuadTree should have a size equal to the number of elements added");
    }

    // Check that all keys are present
    for (unsigned int i = 0; i < num_elements; i++) {
        qt_key_t *key = &keys[i];
        int *result = qt_get(tree, *key);

        if (!qt_has(tree, *key)) {
            free(keys);
            free(tree);
            mu_fail("qt_has should return 1 for a key that was added");
        }
        if (result == NULL) {
            free(keys);
            free(tree);
            mu_fail("qt_get should not return null when retrieving a stored key");
        }
    }

    qt_free(&tree);
    free(keys);
    return MU_TEST_PASS;
}

void all_tests() {
    mu_run_test(test_qt_empty);
    mu_run_test(test_qt_simple_add);
    mu_run_test(test_qt_insert_few);
    mu_run_test(test_qt_insert_many);
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
