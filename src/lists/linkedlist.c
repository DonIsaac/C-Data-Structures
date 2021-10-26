// SPDX-License-Identifier: MIT
#include "linkedlist.h"

#include <errno.h>
#include <string.h>

struct ll_linkedlist {
    GenericLLEntry *head, *tail;
    size_t ent_size;  // Size of each list entry
    int len;          // Number of entries currently in the list
};

// =========================== PRIVATE FUNCTIONS ===============================

int ll_entry_init(ll_entry **entry, char *key, void *data, size_t size) {
    size_t keylen = 0;
    ll_entry *ent = NULL;

    if (!ent || !key || !data) return _CDST_FAILURE;  // Check for null pointers

    // init entry
    ent = *entry = malloc(sizeof(ll_entry));  // Allocate memory for the new entry
    if (!(*entry)) return _CDST_FAILURE;

    ent->next = NULL;

    // init key
    keylen = strlen(key);           // Copy over the key into the entry
    ent->key = malloc(keylen + 1);  // Allocate an extra byte for null terminator
    if (!ent->key) return _CDST_FAILURE;
    strncpy(ent->key, key, keylen + 1);  // Copy over the key. n includes null terminator

    // init data
    ent->data = malloc(size);
    if (!ent->data) return _CDST_FAILURE;
    memcpy(ent->data, data, size);

    return _CDST_SUCCESS;
ll_entry_init_err_key:
    free(*entry);
    *entry = NULL;

    return _CDST_FAILURE;
}

// ============================ PUBLIC FUNCTIONS ===============================

int ll_new(LinkedList **ll) {
    if (!ll) return _CDST_FAILURE;  // ll is a null pointer

    *ll = malloc(sizeof(LinkedList));  // Allocate memory for the list
    if (!(*ll)) return _CDST_FAILURE;

    (*ll)->head = NULL;
    (*ll)->tail = NULL;

    return _CDST_SUCCESS;
}

int ll_add(LinkedList *ll, char *key, void *data, size_t size) {
    if (!ll || !key || !data || size < 0) return _CDST_FAILURE;  // Fail if pointers are null or size is invalid

    ll_entry *curr_tail = ll->tail;
    return _CDST_FAILURE;
}
