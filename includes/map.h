/**
 * @file map.h
 * @author Donald Isaac
 * @brief
 * @version 0.1
 * @date 2021-10-26
 *
 * @copyright Copyright (c) 2021. MIT License.
 *
 * @defgroup map Map
 *
 * A data structure that maps keys to values. Maps cannot contain duplicate
 * keys.
 *
 */
#ifndef __CDS_MAP_H__
#define __CDS_MAP_H__

#include "mapkey.h"

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
#define _MAP_FAILURE -1

#endif
