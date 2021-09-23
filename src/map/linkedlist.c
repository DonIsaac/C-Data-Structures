#include "linkedlist.h"

#include <errno.h>
#include <string.h>

typedef struct _ll_entry {
    char *key;
    void *data;
    struct __ll_entry *next;
} ll_entry;

struct ll_linkedlist {
    ll_entry *head;
    ll_entry *tail;
};

// =========================== PRIVATE FUNCTIONS ===============================

int ll_entry_init(ll_entry **entry, char *key, void *data, size_t size) {
   size_t keylen = 0;
   ll_entry *ent = NULL;

   if (!ent || !key || !data) return FAILURE; // Check for null pointers

   // init entry
   ent = *entry = malloc(sizeof(ll_entry));   // Allocate memory for the new entry
   if (!(*entry)) return FAILURE;

   ent->next = NULL;

   // init key
   keylen = strlen(key);                      // Copy over the key into the entry
   ent->key = malloc(keylen + 1);             // Allocate an extra byte for null terminator
   if (!ent->key) return FAILURE;
   strncpy(ent->key, key, keylen + 1);        // Copy over the key. n includes null terminator

   // init data
   ent->data = malloc(size);
   if (!ent->data) return FAILURE;
   memcpy(ent->data, data, size);

   return SUCCESS;
ll_entry_init_err_key:
   free(*entry);
   *entry = NULL;

   return FAILURE;
}

// ============================ PUBLIC FUNCTIONS ===============================



int ll_new(LinkedList **ll) {
   if (!ll) return FAILURE;          // ll is a null pointer

   *ll = malloc(sizeof(LinkedList)); // Allocate memory for the list
   if (!(*ll)) return FAILURE;

   (*ll)->head = NULL;
   (*ll)->tail = NULL;

   return SUCCESS;
}

int ll_add(LinkedList *ll, char *key, void *data, size_t size) {
   if (!ll || !key || !data || size < 0) return FAILURE; // Fail if pointers are null or size is invalid

   ll_entry *curr_tail = ll->tail;
   return FAILURE;
}
