/**
 * Karim Boujana Marcucci.
 */

double f(double x);

double trapezis (int n , double a , double b) {

    /* Inicializacion de valores. */
    double T = 0, h = (b-a)/n;
    int i;

    /* Aplicamos la fórmula del cálculo de las áreas de los trapecios. */
    T += (f(a)/2.0) + (f(b)/2.0);
    for (i = 1; i < n-1; i++) T += f(a + i*h);
    T *= h;
    return T;

}