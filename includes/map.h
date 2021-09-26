#ifndef __MAP_H__
#define __MAP_H__

/**
 * @brief An operation was successfully performed.
 */
#define _MAP_SUCCESS 1
/**
 * @brief An operation was successfully performed, but an existing map entry
 * was replaced.
 */
#define _MAP_SUCCESS_REPLACED 2

/**
 * @brief An operation failed.
 *
 * `errno` is usually set on failures.
 */
#define _MAP_FAILURE 0

#endif
