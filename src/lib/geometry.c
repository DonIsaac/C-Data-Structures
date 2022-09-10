#include "geometry.h"

#include <math.h>
#include "epsilon.h"

int pointd_eq(pointd_t a, pointd_t b) {
    return cmp_d(a.x, b.x) == 0
        && cmp_d(a.y, b.y) == 0;
}

inline double pointd_distance(pointd_t a, pointd_t b) {
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}
