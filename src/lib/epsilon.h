#ifndef __EPSILON_H__
#define __EPSILON_H__

double epsilon_d();
float epsilon_f();

/**
 * @brief Compares two doubles for equality.
 * 
 * @param a The first double.
 * @param b The second double.
 * 
 * @return int `-1` if `a < b`, `0` if `a == b`, `1` if `a > b`.
 *
 */
int cmp_d(const double a, const double b);

/**
 * @brief Compares two floats for equality.
 * 
 * @param a The first floats.
 * @param b The second floats.
 * 
 * @return int `-1` if `a < b`, `0` if `a == b`, `1` if `a > b`.
 *
 */
int cmp_f(const float a, const float b);

#endif
