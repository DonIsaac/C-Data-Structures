#ifndef __POINT_H__
#define __POINT_H__

// typedef double pointd_t[2];
typedef struct pointd {
    double x;
    double y;
} pointd_t;

/**
 * @brief Checks if two points are equal.
 *
 * @param a First point.
 * @param b Second point.
 *
 * @return 1 if the points are equal, 0 otherwise.
 */
int pointd_eq(pointd_t a, pointd_t b);

/**
 * @brief Calculates the euclidean distance between two points.
 *
 * @param a First point.
 * @param b Second point.
 *
 * @return The euclidean distance between the two points.
 */
double pointd_dist(pointd_t a, pointd_t b);

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
double pointd_distm(pointd_t a, pointd_t b);
#endif
