/**
 * Karim Boujana Marcucci.
 */

#include <math.h> 

double condV(int m, double tol) {
    /** 
     * Calcularemos el número de condición de la matriz de Vandermonde de tamaño m por m.
     */

     double x[m], temp_x;
     int i, j;

     for (i = 0 ; i < m; i++) x[i] = -1 + ((2.0*i)/(m-1)); /* Puntos equiespaciados en el intervalo -1, 1.*/

     /* Creemos la matriz de Vandermonde. */
     double **V = (double**) calloc(m, sizeof(double*));
    for (i= 0 ; i < m ; i++) {
        double *fila = (double*) calloc(m, sizeof(double));
        V[i] = fila;
        temp_x = x[i];
        for (j=0 ; j < m ; j++) {
            fila[j] = temp_x;
            temp_x *= x[i];
        }
    }

}