#include "quadtree.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/geometry.h"

#define NUM_CHILDREN 4
#define NW 0
#define NE 1
#define SW 2
#define SE 3

typedef struct qt_node {
    qt_key_t key;                           /* The key used to identify the data */
    void *data;                             /* A pointer to the data stored in the node */
    size_t size;                            /* The size of the data stored in the node */
    struct qt_node *children[NUM_CHILDREN]; /* The children of the node (NW, NE, SW, SE) */
} qt_node;

struct qt_quadtree {
    qt_node *root;
};

// =================================== UTILS ===================================

int _qt_locate(qt_key_t key, qt_key_t point) {
    if (point.x < key.x) {
        return point.y < key.y ? SW : NW;
    } else {
        return point.y < key.y ? SE : NE;
    }
}

// =================================== NODE ====================================

map_status_t _qt_node_init(qt_node **node, qt_key_t key, void *data, size_t size) {
    if (node == NULL) return _MAP_FAILURE;

    // Allocate memory for the new node
    *node = malloc(sizeof(qt_node));
    if (*node == NULL) return _MAP_FAILURE;

    // Allocate memory for the data
    (*node)->data = malloc(size);
    if ((*node)->data == NULL) {
        free(*node);
        return _MAP_FAILURE;
    }

    // Copy over key, size, and data into the new node
    (*node)->key = key;
    memcpy((*node)->data, data, size);
    (*node)->size = size;

    // Node is a leaf and has no children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        (*node)->children[i] = NULL;
    }

    return _MAP_SUCCESS;
}

void _qt_node_free(qt_node *node) {
    if (node == NULL) return;

    free(node->data);
    for (int i = 0; i < NUM_CHILDREN; i++) {
        _qt_node_free(node->children[i]);
    }
    free(node);
}

int _qt_node_size(qt_node *node) {
    if (node == NULL) return 0; // base case

    int size = 1;
    for (int i = 0; i < NUM_CHILDREN; i++) {
        size += _qt_node_size(node->children[i]);
    }

    return size;
}

map_status_t _qt_node_add(qt_node *node, qt_key_t key, void *data, size_t size) {
    if (node == NULL) return _MAP_FAILURE;

    // If the key is already in the tree, replace the data
    if (pointd_eq(node->key, key)) {
        // Free the old data, al
        free(node->data);
        node->data = malloc(size);
        if (node->data == NULL) return _MAP_FAILURE;

        // Copy over new data and it's size
        memcpy(node->data, data, size);
        node->size = size;

        return _MAP_SUCCESS_REPLACED;
    }

    // Pick which quadrant the child should be in
    int child = _qt_locate(node->key, key);

    // If the key is not in the tree, add it
    if (node->children[child] == NULL) {
        return _qt_node_init(&node->children[child], key, data, size);
    } else {
        return _qt_node_add(node->children[child], key, data, size);
    }
}

void *_qt_node_get(qt_node *node, qt_key_t key) {
    if (node == NULL) return NULL;

    // If the key is in the tree, return the data
    if (pointd_eq(node->key, key)) {
        return node->data;
    }

    // Pick which quadrant the child should be in, then recurse
    int child = _qt_locate(node->key, key);
    return _qt_node_get(node->children[child], key);
}

int _qt_node_has(qt_node *node, qt_key_t key) {
    if (node == NULL) return 0;

    // If the key is in the tree, return 1
    if (pointd_eq(node->key, key)) {
        return 1;
    }

    // Pick which quadrant the child should be in, then recurse
    int child = _qt_locate(node->key, key);
    return _qt_node_has(node->children[child], key);
}

map_status_t _qt_node_remove(qt_node *node, qt_key_t key) {
    // TODO: This function is not complete
    if (node == NULL) return _MAP_FAILURE;

    // Pick which quadrant the child should be in
    int child = _qt_locate(node->key, key);

    // If the key is in the tree, remove it
    if (node->children[child] != NULL) {
        if (pointd_eq(node->children[child]->key, key)) {
            _qt_node_free(node->children[child]);
            node->children[child] = NULL;
            return _MAP_SUCCESS;
        } else {
            return _qt_node_remove(node->children[child], key);
        }
    }

    return _MAP_FAILURE;
}

// ================================= QUADTREE ==================================

map_status_t qt_init(QuadTree **tree) {
    if (tree == NULL) {
        return _MAP_FAILURE;
    }

    *tree = malloc(sizeof(QuadTree));
    if (*tree == NULL) {
        return _MAP_FAILURE;
    }

    (*tree)->root = NULL;

    return _MAP_SUCCESS;
}

void qt_free(QuadTree **tree) {
    // Nothing to free
    if (tree == NULL || *tree == NULL) {
        return;
    }

    // Free root node
    qt_node *root = (*tree)->root;
    if (root != NULL) {
        _qt_node_free(root);
    }

    // Free tree
    free(*tree);
    *tree = NULL;
}

int qt_height(QuadTree *tree) {
    // not implemented
    if (tree == NULL) return 0;
    return -1;
}

int qt_size(QuadTree *tree) {
    if (tree == NULL || tree->root == NULL) return 0;

    return _qt_node_size(tree->root);
}

map_status_t qt_add(QuadTree *tree, qt_key_t key, void *data, size_t size) {
    if (tree == NULL) return _MAP_FAILURE;

    // Create a new node if this tree has no root, otherwise insert it
    // into the root
    if (tree->root == NULL) {
        return _qt_node_init(&tree->root, key, data, size);
    } else {
        return _qt_node_add(tree->root, key, data, size);
    }
}

void *qt_get(QuadTree *tree, qt_key_t key) {
    if (tree == NULL || tree->root == NULL) return NULL;

    return _qt_node_get(tree->root, key);
}

int qt_has(QuadTree *tree, qt_key_t key) {
    if (tree == NULL || tree->root == NULL) return 0;
    return _qt_node_has(tree->root, key);
}

map_status_t qt_remove(QuadTree *tree, qt_key_t key) {
    if (tree == NULL || tree->root == NULL) return _MAP_FAILURE;
    return _qt_node_remove(tree->root, key);
}
