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
double pointd_distance(pointd_t a, pointd_t b);

#endif
