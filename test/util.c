#include "util.h"
#include <stdlib.h>

double drandom_r() {
    // create a random rational number
    int a = rand();
    int b = rand();
    double sign = rand() % 2 ? 1.0 : -1.0;

    // Prevent division by zero
    if (b == 0) {
        b = 1;
    }

    return sign * (double) a / (double) b;
}

