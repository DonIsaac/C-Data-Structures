// SPDX-License-Identifier: MIT
#include "bintree.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <sys/param.h>

typedef struct bt_node {
    char *key;             // entry lookup key
    void *data;            // entry value
    size_t size;           // size of data
    struct bt_node *left,  // left child node
        *right;            // right child node
} bt_node;

struct bt_bintree {
    bt_node *root;
};

// =============================== PRIVATE UTIL ================================

int _bt_num_children(bt_node *node) {
    assert(node);
    // Both children are null, node is leaf
    if (!node->left && !node->right)
        return 0;

    // Only left or right child is non-null
    else if (
        (node->left && !node->right) ||
        (node->right && !node->left))
        return 1;

    // Neither children are null
    else
        return 2;
}
bool _bt_node_is_leaf(bt_node *node) {
    return _bt_num_children(node) == 0;
}

bt_node *_bt_min(bt_node *node) {
    if (!node) return NULL;

    switch (_bt_num_children(node)) {
        case 0:
            return node;
        case 1:
            if (node->left) {
                return _bt_min(node->left);
            } else {
                return node;
            }
        default:
            return _bt_min(node->left);
    }
}

// =============================== INIT/DESTROY  =================================

int _bt_node_init(bt_node **node, char *key, void *data, size_t size) {
    bt_node *n = NULL;
    size_t keylen = 0;

    // Check parameters
    if (!node || !key || !data) return _MAP_FAILURE;

    // Allocate memory for new node
    n = *node = malloc(sizeof(bt_node));
    if (!n) return _MAP_FAILURE;

    // The node has no children
    n->left = NULL;
    n->right = NULL;

    // copy over key string
    keylen = strlen(key);
    n->key = malloc(keylen + 1);  // Extra byte for null terminator
    if (!n->key) return _MAP_FAILURE;  // TODO: this will leak memory
    strncpy(n->key, key, keylen + 1);

    // copy over entry data
    n->size = size;
    n->data = malloc(size);
    if (!n->data) return _MAP_FAILURE;  // TODO: this will leak memory
    memcpy(n->data, data, size);

    return _MAP_SUCCESS;
}

int bt_init(BinTree **tree) {
    BinTree *t = NULL;

    if (!tree) return _MAP_FAILURE;

    t = *tree = malloc(sizeof(BinTree));
    if (!t) return _MAP_FAILURE;

    t->root = NULL;

    return _MAP_SUCCESS;
}

void _bt_node_free(bt_node *node) {
    // Node must point to a leaf node
    assert(node);
    // assert(node->left == NULL);
    // assert(node->right == NULL);

    // Free node memory resources
    free(node->key);
    free(node->data);
    free(node);
}

void _bt_node_free_all(bt_node *node) {
    // Base case
    if (!node) return;

    // Recursively free children
    _bt_node_free_all(node->left);
    _bt_node_free_all(node->right);

    // Free current node
    _bt_node_free(node);
}

void bt_free(BinTree **tree) {
    if (!tree || !(*tree)) return;

    // Free root if it exists
    if ((*tree)->root) {
        _bt_node_free_all((*tree)->root);
    }

    free(*tree);
    *tree = NULL;
}

// ================================ HEIGHT/SIZE ================================

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
    if (!tree || !tree->root) return _MAP_FAILURE;

    return _bt_size(tree->root);
}

// ================================= INSERTION =================================

int _bt_add(bt_node *node, char *key, void *data, size_t size) {
    int cmp;  // Comparison between node key and target key

    // Check params
    if (!node || !key || !data) return _MAP_FAILURE;

    cmp = strcmp(node->key, key);
    if (!cmp) {
        // Entry with key already exists, replace data
        free(node->data);
        node->data = malloc(size);
        if (!node->data) return _MAP_FAILURE;
        memcpy(node->data, data, size);
        node->size = size;
        return _MAP_SUCCESS_REPLACED;

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
    if (!tree || !key || !data) return _MAP_FAILURE;

    // Tree is empty, create a new root node
    if (!tree->root) {
        return _bt_node_init(&tree->root, key, data, size);
    }

    // Tree is not empty, recursively insert into root node
    return _bt_add(tree->root, key, data, size);
}

// =================================== READ ====================================

void *_bt_get(bt_node *node, char *key) {
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

void *bt_get(BinTree *tree, char *key) {
    if (!tree || !key) return NULL;  // Bad parameters
    if (!tree->root) return NULL;    // Tree is empty

    return _bt_get(tree->root, key);
}

int bt_has(BinTree *tree, char *key) {
    if (!tree || !key) return false;  // Bad parameters

    return _bt_get(tree->root, key) == NULL ? false : true;
}

// ================================= DELETION ==================================

bt_node *_bt_remove(bt_node *node, char *key, int *status) {
    int cmp;

    assert(key);
    assert(status);

    // Base case: key not found.
    if (!node) {
        *status = 0;
        return NULL;
    }

    cmp = strcmp(node->key, key);
    if (!cmp) {  // Base case: entry found, delete current node
        if (_bt_node_is_leaf(node)) {
            *status = _MAP_SUCCESS;
            _bt_node_free(node);
            return NULL;

        } else if (  // Node only has 1 child;
            (node->left && !node->right) ||
            (node->right && !node->left)) {
            bt_node *child = node->left ? node->left : node->right;  // Get child subtree
            *status = _MAP_SUCCESS;
            _bt_node_free(node);
            return child;

        } else {  // Node has two children, replace self with right child's min node
            bt_node *right_min = _bt_min(node->right);
            assert(right_min);

            // Replace node's key with right min's key
            size_t keylen = strlen(right_min->key); // Free old key
            free(node->key);
            node->key = malloc(keylen + 1);
            if (!node->key) return NULL; // TODO: What do here?
            strncpy(node->key, right_min->key, keylen + 1); // Copy key to node

            // Replace node's value with right min's value
            free(node->data);                    // Free old data
            node->size = right_min->size;
            node->data = malloc(right_min->size);
            if (!node->data) return NULL; // TODO: What do here?
            memcpy(node->data, right_min->data, right_min->size); // Copy data to node

            // Remove (now duplicate) min node from right subtree
            node->right = _bt_remove(node->right, right_min->key, status);
            *status = 1;

            return node;
        }

    } else if (cmp > 0) {
        // node key > target key, go left
        node->left = _bt_remove(node->left, key, status);
        return node;

    } else {
        // node key < target key, go right
        node->right = _bt_remove(node->right, key, status);
        return node;
    }
}

int bt_remove(BinTree *tree, char *key) {
    int status = _MAP_FAILURE;

    if (!tree || !key) return _MAP_FAILURE;

    tree->root = _bt_remove(tree->root, key, &status);

    return status;
}
