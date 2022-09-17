#ifndef __MAP_H__
#define __MAP_H__

typedef int map_status_t;

/**
 * @brief An operation was successfully performed.
 */
#define _MAP_SUCCESS ((map_status_t)1)
/**
 * @brief An operation was successfully performed, but an existing map entry
 * was replaced.
 */
#define _MAP_SUCCESS_REPLACED ((map_status_t)2)

/**
 * @brief An operation failed.
 *
 * `errno` is usually set on failures.
 */
#define _MAP_FAILURE ((map_status_t)0)

#endif
