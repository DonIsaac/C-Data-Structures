#include "bintree.h"

#include <math.h>
#include <sys/param.h>
#include <string.h>

typedef struct bt_node
{
    char *key;
    void *data;
    struct bt_node *left, *right;
} bt_node;

struct bt_bintree {
    bt_node *root;
};

int _bt_node_init(bt_node **node, char *key, void *data, size_t size) {
    bt_node *n = NULL;
    size_t keylen = 0;

    // Check parameters
    if (!node || !key || !data) return FAILURE;

    // Allocate memory for new node
    n = *node = malloc(sizeof(bt_node));
    if (!n) return FAILURE;

    // The node has no children
    n->left = NULL;
    n->right = NULL;

    // copy over key string
    keylen = strlen(key);
    n->key = malloc(keylen + 1); // Extra byte for null terminator
    if (!n->key) return FAILURE; // TODO: this will leak memory
    strncpy(n->key, key, keylen + 1);

    // copy over entry data
    n->data = malloc(size);
    if (!n->data) return FAILURE; // TODO: this will leak memory
    memcpy(n->data, data, size);

    return SUCCESS;
}

int bt_init(BinTree **tree) {
    BinTree *t = NULL;

    if (!tree) return FAILURE;

    t = *tree = malloc(sizeof(BinTree));
    if (!t) return FAILURE;

    t->root = NULL;

    return SUCCESS;
}

int _bt_height(bt_node *node) {
    if (!node) return 0;
    return 1 + MAX(_bt_height(node->left), _bt_height(node->right));
}

int bt_height(BinTree *tree) {
    if (!tree || !tree->root) return 0;

    return _bt_height(tree->root);
}

int _bt_size(bt_node *node) {
    if (!node)
        return 0;
    else
        return 1 + _bt_size(node->left) + _bt_size(node->right);
}

int bt_size(BinTree *tree) {
    if (!tree || !tree->root) return FAILURE;

    return _bt_size(tree->root);
}

int _bt_add(bt_node *node, char *key, void *data, size_t size) {
    int cmp; // Comparison between node key and target key

    // Check params
    if (!node || !key || !data) return FAILURE;

    cmp = strcmp(node->key, key);
    if (!cmp) {
        // Entry with key already exists, replace data
        free(node->data);
        node->data = malloc(size);
        if (!node->data) return FAILURE;
        memcpy(node->data, data, size);
        return SUCCESS_REPLACED;

    } else if (cmp > 0) {
        // node key > target key, so go left
        if (!node->left) {
            // base case: no left subtree, create new leaf node
            return _bt_node_init(&node->left, key, data, size);
        } else {
            // left subtree exists, recursively insert into it
            return _bt_add(node->left, key, data, size);
        }

    } else {
        // node key < target key, so go right
        if (!node->right) {
            // base case: no right subtree, create new leaf node
            return _bt_node_init(&node->right, key, data, size);
        } else {
            // right subtree exists, recursively insert into it
            return _bt_add(node->right, key, data, size);
        }
    }
}

int bt_add(BinTree *tree, char *key, void *data, size_t size) {
    if (!tree || !key || !data) return FAILURE;

    // Tree is empty, create a new root node
    if (!tree->root) {
        return _bt_node_init(&tree->root, key, data, size);
    }

    // Tree is not empty, recursively insert into root node
    return _bt_add(tree->root, key, data, size);
}

void* _bt_get(bt_node *node, char *key) {
    int cmp;

    if (!node || !key) return NULL;

    cmp = strcmp(node->key, key);

    if (!cmp) {
        // Entry found, return data
        return node->data;
    } else if (cmp > 0) {
        // node key > target key, go left
        return _bt_get(node->left, key);
    } else {
        // node key < target key, go right
        return _bt_get(node->right, key);
    }
}

void* bt_get(BinTree *tree, char *key) {
    if (!tree || !key) return NULL; // Bad parameters
    if (!tree->root) return NULL;   // Tree is empty

    return _bt_get(tree->root, key);
}
