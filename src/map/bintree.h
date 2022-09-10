/**
 * @file bintree.h
 * @brief A key/value map implemented as a Binary Search Tree
 *
 * @author Donald Isaac
 * @version 0.0.1
 * @date 2021-09-24
 * @copyright Copyright (c) 2021. MIT License
 *
 * @defgroup bt Binary Search Tree
 * This implementation is able to store heterogenous data of variable size.
 * Each data entry is stored under a unique search key, which is a string.
 *
 * Note that this tree is only able to store one entry per unique key. Inserting
 * with a duplicate key will cause the existing entry to be overwritten.
 * Keys are compared using `strcmp`.
 */
#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdlib.h>

#include "map.h"

/**
 * @brief A Binary Search Tree storing key/value pairs.
 *
 * This implementation is able to store heterogenous data of variable size.
 * Each data entry is stored under a unique search key, which is a string.
 *
 * Note that this tree is only able to store one entry per unique key. Inserting
 * with a duplicate key will cause the existing entry to be overwritten.
 * Keys are compared using `strcmp`.
 *
 * This implementation assumes that it "owns" its data. Insertion with replacement
 * and deletion will cause entries to be freed. Because of this, storing data
 * pointers long-term is ill-advised. Prefer entry retrieval (`bt_get`) over
 * pointer storage.
 *
 * @ingroup bt
 */
typedef struct bt_bintree BinTree;

/**
 * @brief Constructs a new BinTree.
 *
 * @ingroup bt
 *
 * @param tree A pointer to the tree to construct.
 *
 * @return int 1 on success, 0 on failure.
 */
map_status_t bt_init(BinTree **tree);

/**
 * @brief Destroys an existing BinTree and frees all resources associated with it.
 *
 * After destruction, the BinTree will be set to `NULL`.
 *
 * @ingroup bt
 *
 * @param tree A pointer to the tree to destroy.
 */
void bt_free(BinTree **tree);

/**
 * @brief Calculates the height of a BinTree.
 *
 * @ingroup bt
 *
 * @param tree The target tree.
 *
 * @return int The height of the tree, or 0 on failure. Check `errno` to
 * distinguish between a tree with a height of `0` and failures.
 */
int bt_height(BinTree *tree);

/**
 * @brief Gets the number of key/value entries in a BinTree.
 *
 * @ingroup bt
 *
 * @param tree The target tree.
 *
 * @return int The number of entries in the tree. On failure, 0 is returned.
 * To distinguish between a tree with no entries and a failure, check `errno`.
 */
int bt_size(BinTree *tree);

/**
 * @brief Gets the value stored in the smallest entry.
 *
 * @ingroup bt
 *
 * @param tree The target tree.
 *
 * @return The smallest entry's stored data. If the tree is empty, `NULL` is
 * returned.
 */
void *bt_min(BinTree *tree);

/**
 * @brief Gets the value stored in the largest entry.
 *
 * @ingroup bt
 *
 * @param tree The target tree.
 *
 * @return The largest entry's stored data. If the tree is empty, `NULL` is
 * returned.
 */
void *bt_max(BinTree *tree);

/**
 * @brief Inserts an entry into a tree.
 *
 * If an entry under `key` already exists, it is replaced. The incumbent data
 * will be removed and its memory will be freed. Reading/writing to an overwritten
 * entry has undefined behavior.
 *
 * Both the entry key and data are copied over into the tree. As such, modifying
 * the original key or data after insertion will have no effect on the tree.
 *
 * @ingroup bt
 *
 * @param tree The BST to insert into.
 * @param key  The entry key.
 * @param data The data stored in the entry.
 * @param size The size of `data`
 *
 * @return int A positive number on success, 0 on failure. If an existing entry
 * is replaced, 2 is returned.
 */
map_status_t bt_add(BinTree *tree, char *key, void *data, size_t size);

/**
 * @brief Searches the BinTree for an entry.
 *
 * Pointers returned from this function should be used for short-term, local
 * reads and writes. Because the tree "owns" the entry resources, following
 * operations may free the memory segment pointed to by the pointer. Do not
 * store the pointer returned by this function for long-term use. Instead,
 * re-invoke this function when you need to access stored data.
 *
 * @ingroup bt
 *
 * @param tree The tree to search.
 * @param key The key the entry is stored under.
 *
 * @return void* A pointer to the data stored in the entry. If no entry exists
 * for the given key, `NULL` is returned. On error, `NULL` is returned and
 * `errno` is set.
 */
void *bt_get(BinTree *tree, char *key);

// void *bt_get_min(BinTree *tree);
// void *bt_get_max(BinTree *tree);

/**
 * @brief Checks if an entry exists under a specific search key in a BinTree.
 *
 * @ingroup bt
 *
 * @param tree The tree to search.
 * @param key  The entry key to check.
 *
 * @return int 1 if an entry exists for `key`, 0 if one does not.
 */
int bt_has(BinTree *tree, char *key);

/**
 * @brief Removes an entry from a BinTree, freeing its memory resources.
 *
 * @ingroup bt
 *
 * @param tree The tree to remove the entry from.
 * @param key  The entry key.
 *
 * @return int 1 if the entry exists ans was successfully deleted. If no entry
 * exists for the given key, 0 is returned. On error, 0 is returned and `errno`
 * is set.
 */
map_status_t bt_remove(BinTree *tree, char *key);
#endif
