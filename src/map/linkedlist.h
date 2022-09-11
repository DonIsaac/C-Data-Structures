/**
 * @file linkedlist.h
 *
 * @brief A key/value map implemented with a Doubly Linked List.
 *
 * @author Donald Isaac
 * @version 0.0.1
 * @date 2021-09-23
 * @copyright Copyright (c) 2021. MIT License
 *
 * @defgroup ll Linked List
 *
 * A key/value map implemented with a Doubly Linked List.
 */
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdlib.h>

#include "map.h"

typedef struct ll_linkedlist LinkedList;

/**
 * @brief Constructs a new LinkedList
 *
 * @ingroup ll
 *
 * @param ll Pointer to the list to initialize.
 *
 * @return 1 if a new LinkedList is successfully created. On error, `errno` is
 * set and 0 is returned.
 */
int ll_new(LinkedList **ll);

/**
 * @brief Destroys a LinkedList, freeing all resources associated with it.
 *
 * @ingroup ll
 *
 * After destruction, the list pointed to by `ll` will be set to `NULL`.
 *
 * @param ll Pointer to the list to destroy.
 *
 * @return 0 on success or an error code on failure.
 */
int ll_free(LinkedList **ll);

/**
 * @brief Inserts a key/value entry into a LinkedList.
 *
 * Entry keys must be unique. If an entry already exists under the
 * desired key, this function fails.
 *
 * @ingroup ll
 *
 * @param ll   The list to insert into.
 * @param key  The entry key. Can be used later to locate this entry.
 * @param data The data stored in the entry.
 * @param size The size of `data`
 *
 * @return 1 on success or 0 on failure
 */
int ll_add(LinkedList *ll, char *key, void *data, size_t size);

/**
 * @brief Retrieves an entry stored in the list.
 *
 * @ingroup ll
 *
 * @param ll  The list to retrieve the entry from.
 * @param key The entry key.
 * @param dst Where to put the data stored under `key`, if found.
 *
 * @return 1 if the entry is found. If no entry exists under the desired key,
 * 0 is returned. If an error occurs, `errno` is set and -1 is returned.
 */
int ll_get(LinkedList *ll, char *key, void *dst);

/**
 * @brief Removes an entry stored in a LinkedList.
 *
 * @ingroup ll
 *
 * @param ll The list to remove the entry from.
 * @param key The entry key.
 *
 * @return 1 if an entry exists under the key and is successfully removed.
 * If no entry exists, 0 is returned. On error, `errno` is set and -1 is
 * returned.
 */
int ll_remove(LinkedList *ll, char *key);

/**
 * @brief Checks if an entry exists for a key.
 *
 * @ingroup ll
 *
 * @param l   The list to check.
 * @param key The entry key.
 *
 * @return 1 if the list contains an entry under `key`, 0 if it does not.
 * On error, `errno` is set and -1 is returned.
 */
int ll_contains(LinkedList *l, char *key);

/**
 * @brief Gets the number of entries stored in a LinkedList.
 *
 * @ingroup ll
 *
 * @param l The list to get the size of.
 *
 * @return The size of the list. On error, `errno` is set and -1 is returned.
 */
int ll_size(LinkedList *l);
#endif
