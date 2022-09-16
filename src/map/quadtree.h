#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <stdlib.h>

#include "../lib/geometry.h"
#include "map.h"

typedef struct qt_quadtree QuadTree;
// typedef double qt_key_t[2];
typedef point_t qt_key_t;

/**
 * @brief Constructs a new QuadTree.
 *
 * @param tree A pointer to the tree to construct.
 *
 * @returns 0 on success, -1 on failure.
 *
 */
map_status_t qt_init(QuadTree **tree);

void qt_free(QuadTree **tree);

int qt_height(QuadTree *tree);

int qt_size(QuadTree *tree);

map_status_t qt_add(QuadTree *tree, qt_key_t key, void *data, size_t size);

void *qt_get(QuadTree *tree, qt_key_t key);

int qt_has(QuadTree *tree, qt_key_t key);

map_status_t qt_remove(QuadTree *tree, qt_key_t key);
#endif
