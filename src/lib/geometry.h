#ifndef __POINT_H__
#define __POINT_H__

// typedef double pointd_t[2];
typedef struct pointd {
    double x;
    double y;
} pointd_t;

int pointd_eq(pointd_t a, pointd_t b);
double pointd_distance(pointd_t a, pointd_t b);

#endif
