#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdlib.h>
#include "map.h"

typedef struct bt_bintree BinTree;

int bt_init(BinTree **tree);
int bt_free(BinTree **free);

int bt_height(BinTree *tree);
int bt_size(BinTree *tree);

/**
 * @brief Inserts an entry into a tree.
 *
 * If an entry under `key` already exists, it is replaced.
 *
 * @param tree The BST to insert into.
 * @param key  The entry key.
 * @param data The data stored in the entry.
 * @param size The size of `data`
 *
 * @return int A positive number on success, 0 on failure. If an existing entry
 * is replaced, 2 is returned.
 */
int bt_add(BinTree *tree, char *key, void *data, size_t size);
void* bt_get(BinTree *tree, char *key);
int bt_has(BinTree *tree, char *key);
int bt_remove(BinTree *tree, char *key);
#endif
