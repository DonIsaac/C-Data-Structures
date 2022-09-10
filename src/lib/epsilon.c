#include "epsilon.h"

double epsilon_d() {
    static double epsilon = -1.0;

    if (epsilon < 0.0) {
        epsilon = 1.0;
        while (1.0 + epsilon / 2.0 != 1.0)
            epsilon /= 2.0;
    }

    return epsilon;
}

float epsilon_f() {
    static float epsilon = -1.0;

    if (epsilon < 0.0f) {
        epsilon = (float)1;
        while (1.0f + epsilon / 2.0f != 1.0f)
            epsilon /= 2.0f;
    }

    return epsilon;
}

int cmp_d(double a, double b) {
    double epsilon = epsilon_d();
    double diff = a - b;
    return (diff < -epsilon)
               ? -1
           : (diff > epsilon) ? 1
                              : 0;
}

int cmp_f(float a, float b) {
    float epsilon = epsilon_f();
    float diff = a - b;
    return (diff < -epsilon)
               ? -1
           : (diff > epsilon) ? 1
                              : 0;
}
