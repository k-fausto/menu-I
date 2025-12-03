/**
 * Karim Boujana Marcucci.
 */

#include <stdio.h>

double f(double x);
int secant (double x0 , double x1 , int itmax , double *arrel , double tol );

int main(void) {

    double x0, x1, tol, arrel = 0;
    int itmax = 0, result = 3;

    printf("Introduce x0: ");
    scanf("%le", &x0);

    printf("Introduce x1: ");
    scanf("%le", &x1);

    printf("Introduce la tolerancia: ");
    scanf("%le", &tol);

    printf("Introduce la cantidad maxima de iteraciones: ");
    scanf("%d", &itmax);

    if (itmax<0) {
        printf("Cantidad de iteraciones negativa.");
        return -1;
    }

    result = secant(x0, x1, itmax, &arrel, tol);
    /* Comprobamos el resultado. */
    if      (result == 0) printf("Una raiz de la funcion es %15.23le, y su imagen vale: %15.25le", arrel, f(arrel));
    else if (result == 1) printf("Numero maximo de iteraciones.");
    else if (result == 2) printf("Se anula el denominador.");
    else                  printf("Error en la ejecucion de la funcion.");

    /* Para f3, con tolerancia 1e-15, tengo de raíces:  1.41239117202388442251504e+00 y 3.05710354999473787884767e+00. */
    /* Para f4, con tolerancia 1e-15, tengo de raíces: -1.40166702386557484594221e+00 y 4.62311624628456119268094e+00. */

    return 0;
}