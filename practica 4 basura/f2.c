/**
 * Karim Boujana Marcucci.
 */

#include <math.h>
double f(double x) { return (exp(2.0*x)*sin(3.0*x)); }
double f_prim(double x) { return (1.0/13.0) * (2 * exp(2.0*x) * sin(3.0*x) - 3 * exp(2.0*x) * cos(3.0*x)); }