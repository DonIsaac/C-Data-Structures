#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/map/bintree.h"
#include "minunit.h"

#define _BST_TEST_STRLEN 512

int tests_failed = 0;
int tests_run = 0;
int num_assertions = 0;

mu_test(test_bst_empty) {
    int ret = _CDST_SUCCESS;
    BinTree *tree = NULL;

    ret = bt_init(&tree);

    mu_assert("Failed to initialize tree.", ret == _CDST_SUCCESS);
    mu_assert("Empty tree's height is not 0.", bt_height(tree) == 0);
    mu_assert("Empty tree's size is not 0.", bt_size(tree) == 0);

    bt_free(&tree);
    mu_assert("After bt_free(), tree should be NULL.", tree == NULL);

    bt_free(&tree);
    return 0;
}

mu_test(test_bst_add_and_remove_1) {
    int ret = _CDST_SUCCESS;
    BinTree *tree = NULL;
    char *key = "key";
    int data = 5;
    int *data_from_tree = NULL;

    ret = bt_init(&tree);
    mu_assert("Failed to initialize tree.", ret == _CDST_SUCCESS);

    // test insertion
    ret = bt_add(tree, key, &data, sizeof(int));
    mu_assert("Failed to insert entry into empty tree.", ret == _CDST_SUCCESS);

    // test size after insertion
    mu_assert("Tree with 1 entry should have a size of 1.", bt_size(tree) == 1);
    mu_assert("Tree with 1 entry should have a height of 1.", bt_height(tree) == 1);

    // test if entry is retrieveable
    data_from_tree = bt_get(tree, key);
    mu_assert("After insertion, entry should be present in tree.", data_from_tree != NULL);
    mu_assert("Incorrect value retrieved from tree after insertion.", *data_from_tree == data);
    mu_assert("After insertion, bt_has() should return true", bt_has(tree, key));

    // test if entry is removed correctly
    ret = bt_remove(tree, key);
    mu_assert("Removing an existing entry from a tree should return successfully", ret);
    mu_assert("After removal, tree should have a size of 1.", bt_size(tree) == 0);
    mu_assert("After removal, bt_get() should return NULL.", bt_get(tree, key) == NULL);
    mu_assert("After removal, bt_has() should return false.", !bt_has(tree, key));

    bt_free(&tree);
    return 0;
}

mu_test(test_bst_add_duplicate) {
    int ret = _CDST_SUCCESS;
    BinTree *tree = NULL;
    char *key = "key";
    int data1 = 10, data2 = 5;
    int *from_tree = NULL;

    // Construct the tree
    ret = bt_init(&tree);
    mu_assert("Failed to initialize tree.", ret == _CDST_SUCCESS);

    // test insertion
    ret = bt_add(tree, key, &data1, sizeof(int));
    mu_assert("Failed to insert first entry into empty tree.", ret == _CDST_SUCCESS);

    ret = bt_add(tree, key, &data2, sizeof(int));
    mu_assert("Failed to insert duplicate key.", ret != _CDST_FAILURE);
    mu_assert("Inserting a duplicate should return _CDST_SUCCESS_REPLACED", ret == _CDST_SUCCESS_REPLACED);
    mu_assert("After reinsertion, size should be 1", bt_size(tree) == 1);

    from_tree = bt_get(tree, key);
    mu_assert("After reinsertion, data should be most recent value", *from_tree == data2);

    bt_free(&tree);
    return 0;
}

mu_test(test_bst_add_4) {
    int ret = _CDST_SUCCESS;
    BinTree *tree = NULL;
    size_t s = sizeof(int);

    int data[4] = {1, 2, 3, 4};

    // Construct the tree
    ret = bt_init(&tree);
    mu_assert("Failed to initialize tree.", ret == _CDST_SUCCESS);

    // Insert the entries
    mu_assert("Failed to add ('c', 1) to the tree.", ret = bt_add(tree, "c", &(data[0]), s));
    mu_assert("Failed to add ('a', 2) to the tree.", ret = bt_add(tree, "a", &(data[1]), s));
    mu_assert("Failed to add ('d', 3) to the tree.", ret = bt_add(tree, "d", &(data[2]), s));
    mu_assert("Failed to add ('b', 4) to the tree.", ret = bt_add(tree, "b", &(data[3]), s));

    // Check tree properties
    mu_assert("Tree did not have a size of 4 after 4 insertions.", bt_size(tree) == 4);
    mu_assert("Tree did not have a height of 3 after 4 insertions", bt_height(tree) == 3);

    // Check that entries exist and are storing the correct values
    mu_assert("Did not get a value of 1 from entry under key 'c'.", *((int *)bt_get(tree, "c")) == data[0]);
    mu_assert("Did not get a value of 2 from entry under key 'a'.", *((int *)bt_get(tree, "a")) == data[1]);
    mu_assert("Did not get a value of 3 from entry under key 'd'.", *((int *)bt_get(tree, "d")) == data[2]);
    mu_assert("Did not get a value of 4 from entry under key 'b'.", *((int *)bt_get(tree, "b")) == data[3]);

    bt_free(&tree);
    return 0;
}

mu_test(test_bst_remove_empty) {
    int ret = _CDST_SUCCESS;
    BinTree *tree = NULL;

    // Remove nonexistent key from empty tree
    ret = bt_init(&tree);
    ret = bt_remove(tree, "foo");

    mu_assert("When bt_remove is called on an empty tree, it should return 0", !ret);
    mu_assert("When bt_remove is called on an empty tree, it should have a size of 0", bt_size(tree) == 0);

    bt_free(&tree);
    return 0;
}

mu_test(tst_bst_remove_multiple) {
    int ret = _CDST_SUCCESS;
    BinTree *tree = NULL;
    size_t s = sizeof(int);

#define num_entries 7
    char *keys[num_entries] = {"d", "b", "a", "g", "h", "e", "f"};
    int data[num_entries] = {1, 2, 3, 4, 5, 6, 7};
    char *d = keys[0],
         *b = keys[1],
         *a = keys[2],
         *g = keys[3],
         *h = keys[4],
         *e = keys[5],
         *f = keys[6];

    /*
        Create the following tree:
                d
               / \
              b   g
             /   / \
            a   e   h
                 \
                  f
    */
    ret = bt_init(&tree);
    mu_assert("bt_init() failed.", ret != _CDST_FAILURE);
    for (int i = 0; i < num_entries; i++) {
        ret = bt_add(tree, keys[i], &data[i], s);
        mu_assert("Insertion failed.", ret == _CDST_SUCCESS);
        mu_assert("Incorrect size after insertion.", bt_size(tree) == i + 1);
        mu_assert("Entry does not exist in tree after insertion.", bt_has(tree, keys[i]));
    }

    /*
        Remove "b". Afterwards, tree should look like this
                d
               / \
              a   g
                 / \
                e   h
                 \
                  f
    */
    ret = bt_remove(tree, b);
    mu_assert("bt_remove(tree, 'b') failed.", ret == _CDST_SUCCESS);
    mu_assert("Incorrect size after removing 'b', should be 6", bt_size(tree) == 6);
    mu_assert("Key 'b' exists in tree after removal", !bt_has(tree, b));

    /*
        Remove "g". Afterwards, tree should look like this
                d
               / \
              a   h
                 /
                e
                 \
                  f
    */
    ret = bt_remove(tree, g);
    mu_assert("bt_remove(tree, 'g') failed.", ret == _CDST_SUCCESS);
    mu_assert("Incorrect size after removing 'g', should be 5", bt_size(tree) == 5);
    mu_assert("Key 'g' exists in tree after removal", !bt_has(tree, g));
    // e, f, and h should still be in tree
    mu_assert("Key 'e' is not in tree after removing 'g'.", bt_has(tree, e));
    mu_assert("Key 'f' is not in tree after removing 'g'.", bt_has(tree, f));
    mu_assert("Key 'h' is not in tree after removing 'g'.", bt_has(tree, h));

    /*
        Remove "d". Afterwards, tree should look like this
                e
               / \
              a   f
                   \
                    h
    */

    ret = bt_remove(tree, d);
    mu_assert("bt_remove(tree, 'd') failed.", ret == _CDST_SUCCESS);
    mu_assert("Incorrect size after removing 'd', should be 4", bt_size(tree) == 4);
    mu_assert("Key 'd' exists in tree after removal", !bt_has(tree, d));
    // a, e, f, and h should still be in tree
    mu_assert("Key 'a' is not in tree after removing 'd'.", bt_has(tree, a));
    mu_assert("Key 'e' is not in tree after removing 'd'.", bt_has(tree, e));
    mu_assert("Key 'f' is not in tree after removing 'd'.", bt_has(tree, f));
    mu_assert("Key 'h' is not in tree after removing 'd'.", bt_has(tree, h));

    /*
        Remove "a". Afterwards, tree should look like this
                e
                 \
                  f
                   \
                    h
    */

    ret = bt_remove(tree, a);
    mu_assert("bt_remove(tree, 'a') failed.", ret == _CDST_SUCCESS);
    mu_assert("Incorrect size after removing 'a', should be 3", bt_size(tree) == 3);
    mu_assert("Key 'a' exists in tree after removal", !bt_has(tree, a));
    // e, f, and h should still be in tree
    mu_assert("Key 'e' is not in tree after removing 'a'.", bt_has(tree, e));
    mu_assert("Key 'f' is not in tree after removing 'a'.", bt_has(tree, f));
    mu_assert("Key 'h' is not in tree after removing 'a'.", bt_has(tree, h));

    bt_free(&tree);
    return 0;
}

mu_test(test_bst_min_max) {
    BinTree *tree = NULL;
    size_t s = sizeof(int);
    char key[_BST_TEST_STRLEN] = {0};
    int data;

    // char keys[5] = {"a", "b", "c", "d", "e"};
    // int data[5] = {1, 2, 3, 4, 5};

    bt_init(&tree);

    // Empty trees have no min/max
    mu_assert("bt_max() should return NULL for empty trees.", bt_max(tree) == NULL);
    mu_assert("bt_min() should return NULL for empty trees.", bt_min(tree) == NULL);

    // Add (c, 1). Trees with 1 node have the same min/max
    strcpy(key, "c");
    data = 1;
    bt_add(tree, key, &data, s);
    mu_assert("Expected bt_max() to return *1 after inserting (c, 1).", *((int *)bt_max(tree)) == 1);
    mu_assert("Expected bt_min() to return *1 after inserting (c, 1).", *((int *)bt_min(tree)) == 1);

    // Add (e, 2)
    strcpy(key, "e");
    data = 2;
    bt_add(tree, key, &data, s);
    mu_assert("Expected bt_max() to return *2 after inserting (e, 2).", *((int *)bt_max(tree)) == 2);
    mu_assert("Expected bt_min() to return *1 after inserting (e, 2).", *((int *)bt_min(tree)) == 1);

    // Add (d, 3)
    strcpy(key, "d");
    data = 3;
    bt_add(tree, key, &data, s);
    mu_assert("Expected bt_max() to return *2 after inserting (d, 3).", *((int *)bt_max(tree)) == 2);
    mu_assert("Expected bt_min() to return *1 after inserting (d, 3).", *((int *)bt_min(tree)) == 1);

    // Add (a, 4)
    strcpy(key, "a");
    data = 4;
    bt_add(tree, key, &data, s);
    mu_assert("Expected bt_max() to return *1 after inserting (a, 4).", *((int *)bt_max(tree)) == 2);
    mu_assert("Expected bt_min() to return *4 after inserting (a, 4).", *((int *)bt_min(tree)) == 4);

    // Add (b, 5)
    strcpy(key, "b");
    data = 5;
    bt_add(tree, key, &data, s);
    mu_assert("Expected bt_max() to return *1 after inserting (b, 5).", *((int *)bt_max(tree)) == 2);
    mu_assert("Expected bt_min() to return *4 after inserting (b, 5).", *((int *)bt_min(tree)) == 4);

    bt_free(&tree);
    return 0;
}

void all_tests() {
    mu_run_test(test_bst_empty);
    mu_run_test(test_bst_add_and_remove_1);
    mu_run_test(test_bst_add_duplicate);
    mu_run_test(test_bst_add_4);
    mu_run_test(test_bst_remove_empty);
    mu_run_test(tst_bst_remove_multiple);
    mu_run_test(test_bst_min_max);
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
