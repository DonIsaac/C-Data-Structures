#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdlib.h>

#include "map.h"

typedef struct bt_bintree BinTree;

/**
 * @brief Constructs a new BinTree.
 *
 * @param tree A pointer to the tree to construct.
 *
 * @return int 1 on success, 0 on failure.
 */
int bt_init(BinTree **tree);

/**
 * @brief Destroys an existing Bintree and frees all resources associated with it.
 *
 * After destruction, the BinTree will be set to `NULL`.
 *
 * @param tree A pointer to the tree to destroy.
 *
 * @return int 1 on success, 0 on failure.
 */
int bt_free(BinTree **tree);

/**
 * @brief Calculates the height of a BinTree.
 *
 * @param tree The target tree.
 * @return int The height of the tree, or 0 on failure. Check `errno` to
 * distinguish between a tree with a height of `0` and failures.
 */
int bt_height(BinTree *tree);

/**
 * @brief Gets the number of entries in a BinTree.
 *
 * @param tree The target tree.
 * @return int The number of entries in the tree. On failure, 0 is returned.
 * To distinguish between a tree with no entries and a failure, check `errno`.
 */
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

/**
 * @brief Searches the BinTree for an entry.
 *
 * @param tree The tree to search.
 * @param key The key the entry is stored under.
 *
 * @return void* A pointer to the data stored in the entry. If no entry exists
 * for the given key, `NULL` is returned. On error, `NULL` is returned and
 * `errno` is set.
 */
void *bt_get(BinTree *tree, char *key);

/**
 * @brief Checks if an entry for a key exists.
 *
 * @param tree The tree to search.
 * @param key  The entry key to check.
 *
 * @return int 1 if an entry exists for `key`, 0 if one does not.
 */
int bt_has(BinTree *tree, char *key);
int bt_remove(BinTree *tree, char *key);
#endif
