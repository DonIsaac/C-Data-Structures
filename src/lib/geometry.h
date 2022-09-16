#ifndef __POINT_H__
#define __POINT_H__

#include <stdbool.h>

// typedef double pointd_t[2];
typedef struct point {
    double x;
    double y;
} point_t;

/**
 * @brief A 2-D rectangle.
 * 
 */
typedef struct rect {
    /** min/max values along the X axis. */
    double x[2];
    /** min/max values along the Y axis. */
    double y[2];
} rect_t;

/**
 * @brief Checks if two points are equal.
 *
 * @param a First point.
 * @param b Second point.
 *
 * @return `true` if the points are equal, `false` otherwise.
 */
bool point_eq(const point_t a, const point_t b);

/**
 * @brief Calculates the euclidean distance between two points.
 *
 * @param a First point.
 * @param b Second point.
 *
 * @return The euclidean distance between the two points.
 */
double point_dist(const point_t a, const point_t b);

/**
 * @brief Calculates the Manhattan distance between two points.
 *
 * @details The Manhattan distance, also called the taxicab or city block
 *          distance, is the sum of the absolute differences of their Cartesian
 *          coordinates.
 *
 * @param a First point.
 * @param b Second point.
 *
 * @return The Manhattan distance between the two points.
 */
double point_distm(const point_t a, const point_t b);

bool rect_contains(const rect_t *const rect, const point_t point);
#endif
