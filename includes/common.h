/**
 * @file common.h
 * @author Donald Isaac
 * @brief Common macros, types, and utilities used across the codebase.
 * @version 0.1
 * @date 2021-10-02
 *
 * @copyright Copyright (c) 2021. MIT License
 *
 * @defgroup common Common
 *
 * Common macros, types, and utilities used across the codebase.
 *
 * All macros are prefixed with `_CDST_` to avoid name collisions. This is short
 * for 'C data structures'.
 */
#ifndef __CDST_COMMON_H__
#define __CDST_COMMON_H__

/**
 * @brief An operation was successfully performed.
 *
 * @ingroup common
 */
#define _CDST_SUCCESS 1

/**
 * @brief An operation was successfully performed, but an existing entry
 * was replaced.
 *
 * @ingroup common
 */
#define _CDST_SUCCESS_REPLACED 2

/**
 * @brief An operation failed.
 *
 * `errno` is usually set on failures and should be checked.
 *
 * @ingroup common
 */
#define _CDST_FAILURE 0
#endif
