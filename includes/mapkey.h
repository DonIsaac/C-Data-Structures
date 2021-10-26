#ifndef __CDS_MAPKEY_H__
#define __CDS_MAPKEY_H__

#include "stdlib.h"

/**
 * @brief A function for comparing Map keys.
 *
 * Comparison functions should have the following properties:
 *   1. Symmetric: if `cmp(a, b) == 0`, then `cmp(b, a) == 0`, etc.
 *   2. Transitive: if `cmp(a, b) = 0` and `cmp(b, c) == 0`, then `cmp(a, c) == 0`.
 *
 * @ingroup map
 *
 * @param a The first key
 * @param b The second key
 *
 * @return A negative int if `a < b`, `0` if `a == b`, or a positive int if `a > b`
 */
typedef int (*cmp_t)(void *, void *);

/**
 * @brief
 * @ingroup map
 */
typedef enum _keytype {
    key_undef,  // Guards against accidentally missing types
    key_string,
    key_int
} keytype_t;

/**
 * @brief
 * @ingroup map
 */
typedef struct _key {
    enum _keytype type;
    union {
        int key_i;
        char *key_s;
    };
} key_t;

#define keyi(key) \
    { .type = key_int, .key_i = key }
#define keys(key) \
    { .type = key_string, .key_s = key }

/**
 * @brief
 *
 * @ingroup map
 *
 * @param a
 * @param b
 * @return int
 */
int mkcmp(key_t a, key_t b);

/**
 * @brief
 *
 * @ingroup map
 *
 * @param key
 * @return size_t
 */
size_t mklen(key_t key);

void mkfree(key_t key);
void mkstr(key_t key, char *str, size_t len);

#endif
