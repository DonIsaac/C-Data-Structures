// SPDX-License-Identifier: MIT
#include "bintree.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

#include "common.h"

typedef struct bt_node {
    // char *key;             // entry lookup key
    key_t key;
    void *data;            // entry value
    size_t size;           // size of data
    struct bt_node *left,  // left child node
        *right;            // right child node
} bt_node;

struct bt_bintree {
    bt_node *root;
    keytype_t keytype;
};

// =============================== PRIVATE UTILS ===============================

// #define TYPE int
// #include "generics.h"
// #undef TYPE
#define checkkey(ktype, key) ( \
    ktype == key.type &&       \
    (key.type != key_string || key.key_s))

bt_node *_bt_min(bt_node *node);
bt_node *_bt_max(bt_node *node);

void _bt_node_tostr(bt_node *node, char *buf, size_t bufsize) {
    char keybuf[CDS_STRLEN] = {0};

    if (!buf)
        return;
    if (node == NULL) {
        snprintf(buf, bufsize, "NULL");
        return;
    }
    mkstr(node->key, keybuf, CDS_STRLEN);
    snprintf(buf, bufsize, "node(%s->%p)", keybuf, node->data);
}

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

// =============================== INIT/DESTROY  =================================

int _bt_node_init(bt_node **node, key_t key, void *data, size_t size) {
    bt_node *n = NULL;
    size_t keylen = 0;

    // Check parameters
    if (!node || !data) return _MAP_FAILURE;

    // Allocate memory for new node
    n = *node = malloc(sizeof(bt_node));
    if (!n) return _MAP_FAILURE;

    // The node has no children
    memset(n, '\0', sizeof(bt_node));
    n->key.type = key.type;
    // n->left = NULL;
    // n->right = NULL;

    // copy over key
    if (key.type == key_string) {
        keylen = strlen(key.key_s);
        n->key.key_s = malloc(keylen + 1);
        if (!n->key.key_s) return _MAP_FAILURE;
        strcpy(n->key.key_s, key.key_s);
    } else {
        n->key.key_i = key.key_i;
    }

    // copy over entry data
    n->size = size;
    n->data = malloc(size);
    if (!n->data) return _MAP_FAILURE;  // TODO: this will leak memory
    memcpy(n->data, data, size);

    return _MAP_SUCCESS;
}

int bt_init(BinTree **tree, keytype_t keytype) {
    BinTree *t = NULL;

    if (!tree) return _MAP_FAILURE;
    if (!keytype) return _MAP_FAILURE;

    t = *tree = malloc(sizeof(BinTree));
    if (!t) return _MAP_FAILURE;

    t->root = NULL;
    t->keytype = keytype;

    return _MAP_SUCCESS;
}

void _bt_node_free(bt_node *node) {
    // Node must point to a leaf node
    assert(node);
    // assert(node->left == NULL);
    // assert(node->right == NULL);

    // Free node memory resources
    if (node->key.type == key_string) free(node->key.key_s);
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
    if (!tree) return _MAP_FAILURE;
    if (!tree->root) return 0;

    return _bt_size(tree->root);
}

// ================================= INSERTION =================================

int _bt_add(bt_node *node, key_t key, void *data, size_t size) {
    int cmp;  // Comparison between node key and target key

    // Check params
    assert(node);
    assert(data);
    assert(checkkey(node->key.type, key));

    // cmp = strcmp(node->key.key_s, key);
    cmp = mkcmp(node->key, key);
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

int bt_add(BinTree *tree, key_t key, void *data, size_t size) {
    if (
        !tree ||
        !data ||
        !checkkey(tree->keytype, key)) return _MAP_FAILURE;

    // Tree is empty, create a new root node
    if (!tree->root) {
        return _bt_node_init(&tree->root, key, data, size);
    }

    // Tree is not empty, recursively insert into root node
    return _bt_add(tree->root, key, data, size);
}

// =================================== READ ====================================

void *_bt_get(bt_node *node, key_t key) {
    int cmp;

    if (!node) return NULL;

    // cmp = strcmp(node->key.key_s, key);
    cmp = mkcmp(node->key, key);

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

void *bt_get(BinTree *tree, key_t key) {
    if (!tree || !checkkey(tree->keytype, key)) return NULL;  // Bad parameters
    if (!tree->root) return NULL;                             // Tree is empty

    return _bt_get(tree->root, key);
}

int bt_has(BinTree *tree, key_t key) {
    if (!tree || !checkkey(tree->keytype, key)) return false;  // Bad parameters

    return _bt_get(tree->root, key) == NULL ? false : true;
}

// ================================= DELETION ==================================

bt_node *_bt_remove(bt_node *node, key_t key, int *status) {
    int cmp;
    char strbuf[256] = {0};

    // assert(key);
    assert(status);
    _bt_node_tostr(node, strbuf, 256);
    printf("Removing node: %s\n", strbuf);

    // Base case: key not found.
    if (!node) {
        *status = 0;
        return NULL;
    }
    keytype_t kt = node->key.type;
    assert(checkkey(kt, key));

    // cmp = strcmp(node->key.key_s, key);
    cmp = mkcmp(node->key, key);
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
            if (kt == key_string) {
                size_t keylen = mklen(right_min->key);  // Free old key
                mkfree(node->key);
                if (!(node->key.key_s = malloc(keylen))) return NULL;
                strncpy(node->key.key_s, right_min->key.key_s, keylen);  // Copy key to node
            } else {
                assert(kt == key_int);
                node->key.key_i = right_min->key.key_i;
            }

            // Replace node's value with right min's value
            free(node->data);  // Free old data
            node->size = right_min->size;
            node->data = malloc(right_min->size);
            if (!node->data) return NULL;                          // TODO: What do here?
            memcpy(node->data, right_min->data, right_min->size);  // Copy data to node

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

int bt_remove(BinTree *tree, key_t key) {
    int status = _MAP_FAILURE;

    if (
        !tree ||
        !checkkey(tree->keytype, key)) return _MAP_FAILURE;

    tree->root = _bt_remove(tree->root, key, &status);

    return status;
}

// ================================== MIN/MAX ==================================

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

void *bt_min(BinTree *tree) {
    if (!tree || !tree->root) return NULL;

    bt_node *min = _bt_min(tree->root);

    return min->data;
}

bt_node *_bt_max(bt_node *node) {
    if (!node) return NULL;

    switch (_bt_num_children(node)) {
        case 0:
            return node;
        case 1:
            if (node->right) {
                return _bt_max(node->right);
            } else {
                return node;
            }
        default:
            return _bt_max(node->right);
    }
}

void *bt_max(BinTree *tree) {
    if (!tree || !tree->root) return NULL;

    bt_node *max = _bt_max(tree->root);

    return max->data;
}
