#include "geometry.h"

#include <math.h>

#include "epsilon.h"

int point_eq(const point_t a, const point_t b) {
    return cmp_d(a.x, b.x) == 0 && cmp_d(a.y, b.y) == 0;
}

inline double point_dist(const point_t a, const point_t b) {
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

inline double point_distm(const point_t a, const point_t b) {
    return fabs(a.x - b.x) + fabs(a.y - b.y);
}
