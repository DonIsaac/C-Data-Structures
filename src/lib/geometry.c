#include "geometry.h"

#include <math.h>
#include <stdbool.h>

#include "epsilon.h"

bool point_eq(const point_t a, const point_t b) {
    return cmp_d(a.x, b.x) == 0 && cmp_d(a.y, b.y) == 0;
}

inline double point_dist(const point_t a, const point_t b) {
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

inline double point_distm(const point_t a, const point_t b) {
    return fabs(a.x - b.x) + fabs(a.y - b.y);
}

bool rect_contains(const rect_t *const rect, const point_t point) {
    return point.x >= rect->x[0]  // within left boundary
        && point.x <= rect->x[1]  // within right boundary
        && point.y >= rect->y[0]  // above bottom boundary
        && point.y <= rect->y[1]; // below top boundary
}
