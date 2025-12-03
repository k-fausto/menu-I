/**
 * Karim Boujana Marcucci.
 */

#include <math.h>
double f(double x);

int secant (double x0 , double x1 , int itmax , double * arrel , double tol ) {

    double xk_n1 = x0, xk = x1, xk_p1 = 0, imagen_xk_n1, imagen_xk;
    int i = 0;

    for (i = 0; i < itmax; i++) {

        /* Calculamos las imágenes para ahorrar cálculos después.*/

        imagen_xk_n1 = f(xk_n1);
        imagen_xk = f(xk);
        
        /* El denominador se anula si la diferencia es menor que la tolerancia.*/
        if (fabs(imagen_xk - imagen_xk_n1) < tol) return 2;
        

        /* Actualizo los valores de la sucesión. */
        xk_p1 = xk - imagen_xk * (xk - xk_n1) / (imagen_xk - imagen_xk_n1);
        xk_n1 = xk;
        xk = xk_p1;

        /* Si una de estas dos condiciones se cumple, la sucesión converge.*/
        if (fabs(imagen_xk) < tol || fabs(xk_n1 - xk) < tol) {
            *arrel = xk;
            return 0;
        }

    } 

    return 1;

}