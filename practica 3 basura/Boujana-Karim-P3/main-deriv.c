/**
 * Karim Boujana Marcucci.
 */

#include <math.h> 
#include <stdio.h>


int main(void) {
    
    double x0, h, derivative, approx, approx_cen, error, error_cen;
    int i;
    double der (double x0, double h);
    double derCen (double x0, double h);
    FILE *fptr;
    fptr = fopen("der.dat", "w");
    printf("Introduce un valor x0 en el que evaluar la funcion: ");
    scanf("%le", &x0);
    
    /**
      * Elegimos qué función queremos usar aquí.
      */

    /* Función 1 - exponente.
    -------------------------------------------------------------------------------------
    double f_1(double x);
    
    derivative = exp(x0);

    for (i = 1; i <= 100; i++) {

        h = 1.0/i;
        approx = der(x0, h);
        approx_cen = derCen(x0, h);
        error = fabs(derivative - approx);
        error_cen = fabs(derivative - approx_cen);

        /*Paso, valor de la derivada, aproximación, aproximación centrada, error, y error centrado. */
        /*fprintf(fptr, "%23.15le %23.15le %23.15le %23.15le %23.15le %23.15le\n", h, derivative, approx, approx_cen, error, error_cen);

    }
    */


    /* Función 3 - racional.
    -------------------------------------------------------------------------------------
    double f_2(double x);
    
    derivative = (-50.0*x0)/((1+25*x0*x0)*(1+25*x0*x0));

    for (i = 1; i <= 100; i++) {

        h = 1.0/i;
        approx = der(x0, h);
        approx_cen = derCen(x0, h);
        error = fabs(derivative - approx);
        error_cen = fabs(derivative - approx_cen);

        /*Paso, valor de la derivada, aproximación, aproximación centrada, error, y error centrado. */
        /*fprintf(fptr, "%23.15le %23.15le %23.15le %23.15le %23.15le %23.15le\n", h, derivative, approx, approx_cen, error, error_cen);

    }
    */


    /*Función 4 - f3 al cuadrado.
    -------------------------------------------------------------------------------------*/
    double f_3(double x);
    double f_4(double x);
    
    derivative = (-100.0*x0)/((1+25*x0*x0)*(1+25*x0*x0)*(1+25*x0*x0));

    for (i = 1; i <= 100; i++) {

        h = 1.0/i;
        approx = der(x0, h);
        approx_cen = derCen(x0, h);
        error = fabs(derivative - approx);
        error_cen = fabs(derivative - approx_cen);

        /*Paso, valor de la derivada, aproximación, aproximación centrada, error, y error centrado. */
        fprintf(fptr, "%23.15le %23.15le %23.15le %23.15le %23.15le %23.15le\n", h, derivative, approx, approx_cen, error, error_cen);

    }
    
   

    fclose(fptr);
    return 0;
}