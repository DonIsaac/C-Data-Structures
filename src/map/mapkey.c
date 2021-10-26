#include "mapkey.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

// Compares numeric keys. Behaves like strcmp
#define ncmp(a, b) (a < b ? -1 : a == b ? 0 : 1)

int mkcmp(key_t a, key_t b) {
    assert(a.type == b.type);
    switch (a.type) {
        case key_int:
            return ncmp(a.key_i, b.key_i);
        case key_string:
            return strcmp(a.key_s, b.key_s);
        default:
            // undefined behavior
            return -1;
    }
}

size_t mklen(key_t key) {
    switch (key.type) {
        case key_int:
            return sizeof(int);
        case key_string:
            return strlen(key.key_s) + 1;
        default:
            return 0;
    }
}

void mkfree(key_t key) {
    if (key.type == key_string && key.key_s)
        free(key.key_s);
}

void mkstr(key_t key, char *str, size_t len) {
    switch (key.type) {
        case key_int:
            snprintf(str, len, "%d", key.key_i);
            break;
        case key_string:
            snprintf(str, len, "%s", key.key_s);
            break;
        case key_undef:
            snprintf(str, len, "<undef>");
            break;
        default:
            // undefined behavior
            snprintf(str, len, "<unknown>");
            break;
    }
}
