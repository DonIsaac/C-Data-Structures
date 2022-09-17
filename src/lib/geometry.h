#ifndef __POINT_H__
#define __POINT_H__

#include <stdbool.h>

/**
 * @brief A 2-D point.
 * 
 */
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

/**
 * @brief Checks if a point lies within a rectangle.
 * 
 * @param rect The rectangle
 * @param point The point
 * 
 * @return true if `point` lies within or on the edge of `rect`
 * @return false otherwise
 */
bool rect_contains(const rect_t *const rect, const point_t point);
#endif
