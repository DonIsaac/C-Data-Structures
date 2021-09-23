#include "../src/map/bintree.h"
#include <stdlib.h>
#include <stdio.h>
#include "minunit.h"

int tests_run = 0;

static char *test_bst_empty()
{
    int ret = SUCCESS;
    BinTree *tree = NULL;

    ret = bt_init(&tree);

    mu_assert("Failed to initialize tree.", ret == SUCCESS);
    mu_assert("Empty tree's height is not 0.", bt_height(tree) == 0);
    mu_assert("Empty tree's size is not 0.", bt_size(tree) == 0);

    return 0;
}

static char *test_bst_add_1()
{
    int ret = SUCCESS;
    BinTree *tree = NULL;
    char *key = "key";
    int data = 5;
    int *data_from_tree = NULL;

    ret = bt_init(&tree);
    mu_assert("Failed to initialize tree.", ret == SUCCESS);

    // test insertion
    ret = bt_add(tree, key, &data, sizeof(int));
    mu_assert("Failed to insert entry into empty tree.", ret == SUCCESS);

    // test size after insertion
    mu_assert("Tree with 1 entry should have a size of 1.", bt_size(tree) == 1);
    mu_assert("Tree with 1 entry should have a height of 1.", bt_height(tree) == 1);

    // test if entry is retrieveable
    data_from_tree = bt_get(tree, key);
    mu_assert("After insertion, entry should be present in tree.", data_from_tree != NULL);
    mu_assert("Incorrect value retrieved from tree after insertion.", *data_from_tree == data);

    return 0;
}

static char *test_bst_add_duplicate()
{
    int ret = SUCCESS;
    BinTree *tree = NULL;
    char *key = "key";
    int data1 = 10, data2 = 5;
    int *from_tree = NULL;

    // Construct the tree
    ret = bt_init(&tree);
    mu_assert("Failed to initialize tree.", ret == SUCCESS);

    // test insertion
    ret = bt_add(tree, key, &data1, sizeof(int));
    mu_assert("Failed to insert first entry into empty tree.", ret == SUCCESS);

    ret = bt_add(tree, key, &data2, sizeof(int));
    mu_assert("Failed to insert duplicate key.", ret != FAILURE);
    mu_assert("Inserting a duplicate should return SUCCESS_REPLACED", ret == SUCCESS_REPLACED);
    mu_assert("After reinsertion, size should be 1", bt_size(tree) == 1);

    from_tree = bt_get(tree, key);
    mu_assert("After reinsertion, data should be most recent value", *from_tree == data2);

    return 0;
}

static char *test_bst_add_4() {
    int ret = SUCCESS;
    BinTree *tree = NULL;
    size_t s = sizeof(int);

    int c = 1, a = 2, d = 3, b = 4;
    // int *data = {1, 2, 3, 4};

    // Construct the tree
    ret = bt_init(&tree);
    mu_assert("Failed to initialize tree.", ret == SUCCESS);

    // Insert the entries
    mu_assert("Failed to add ('c', 1) to the tree.", ret = bt_add(tree, "c", &c, s));
    mu_assert("Failed to add ('a', 2) to the tree.", ret = bt_add(tree, "a", &a, s));
    mu_assert("Failed to add ('d', 3) to the tree.", ret = bt_add(tree, "d", &d, s));
    mu_assert("Failed to add ('b', 4) to the tree.", ret = bt_add(tree, "b", &b, s));

    // Check tree properties
    mu_assert("Tree did not have a size of 4 after 4 insertions.", bt_size(tree) == 4);
    mu_assert("Tree did not have a height of 3 after 4 insertions", bt_height(tree) == 3);

    // Check that entries exist and are storing the correct values
    mu_assert("Did not get a value of 1 from entry under key 'c'.", *((int *)bt_get(tree, "c")) == c);
    mu_assert("Did not get a value of 2 from entry under key 'a'.", *((int *)bt_get(tree, "a")) == a);
    mu_assert("Did not get a value of 3 from entry under key 'd'.", *((int *)bt_get(tree, "d")) == d);
    mu_assert("Did not get a value of 4 from entry under key 'b'.", *((int *)bt_get(tree, "b")) == b);

    return 0;
}

static char *all_tests()
{
    mu_run_test(test_bst_empty);
    mu_run_test(test_bst_add_1);
    mu_run_test(test_bst_add_duplicate);
    mu_run_test(test_bst_add_4);

    return 0;
}

int main(int argc, char *argv[])
{
    char *result = all_tests();

    if (result)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("All tests passed\n");
    }

    printf("Ran %d tests\n", tests_run);
    return result != 0;
}
