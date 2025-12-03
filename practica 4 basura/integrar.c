/**
 * Karim Boujana Marcucci.
 */

#include <stdio.h>

double f(double x);
double trapezis (int n , double a , double b);

int main(void) {

    double a = 0, b = 0, area = 0;
    int n = 0;

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
    printf("La integral de f entre a, b es: %15.23le", area);

    return 0;
}