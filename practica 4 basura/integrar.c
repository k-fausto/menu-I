/**
 * Karim Boujana Marcucci.
 */

#include <stdio.h>
#include <math.h>

double f(double x);
double f_prim(double x);
double trapezis (int n , double a , double b);

int main(void) {

    double a = 0, b = 0, area = 0, area_exacta = 0;
    int n = 0, n_exp = 1;
    double tol = 1e-4; /* Reemplazar por tolerancia deseada. */

    printf("Introduce el primer punto del intervalo: ");
    scanf("%le", &a);

    printf("Introduce el segundo punto del intervalo: ");
    scanf("%le", &b);

    printf("Introduce la cantidad de subintervalos: ");
    scanf("%d", &n);

    if (n<0 || b<=a) {
        printf("Valores incorrectos.");
        return -1;
    }

    area = trapezis(n, a, b);
    printf("La integral de f entre a, b, usando el metodo del trapecio es: %15.23le\n", area);

    area_exacta = f_prim(b) - f_prim(a);
    while (fabs(area_exacta - trapezis(n_exp, a, b)) >= tol) n_exp++;
    printf("Para tener la tolerancia deseada se necesitan, calculado de manera experimental, %d intervalos.", n_exp);

    /* Para f1, la cota teórica es de 366 intervalos, y experimentalmente son 173. */
    /* Para f2, la cota teórica es de 16024 intervalos, y experimentalmente son 643. */

    return 0;
}