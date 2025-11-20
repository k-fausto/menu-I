/**
 * Karim Boujana Marcucci.
 */

#include <math.h> 
#include <stdlib.h>

double *triangSup(int n, double **matU, double *b);
int elimGaus(int n, double **a, double *b, double tol);
int pivot(int n, double **matA, int k);
double normMax(int m, double **matA);

double condV(int m, double tol) {
    double *fila;
    double x[m], temp_x;
    int i, j, k;

    /* Puntos equiespaciados en el intervalo -1, 1. */
    for (i = 0; i < m; i++) 
        x[i] = -1 + ((2.0*i)/(m-1));

    /* Creemos la matriz de Vandermonde. */
    double **V = (double**) calloc(m, sizeof(double*));
    for (i = 0; i < m; i++) {
        fila = (double*) calloc(m, sizeof(double));
        V[i] = fila;
        temp_x = 1.0;
        for (j = 0; j < m; j++) {
            fila[j] = temp_x;
            temp_x *= x[i];
        }
    }

    /* Calculemos su inversa. */
    double **V_inverse = (double**) calloc(m, sizeof(double*));
    for (i = 0; i < m; i++) 
        V_inverse[i] = (double*) calloc(m, sizeof(double));
    
    for (i = 0; i < m; i++) {

        /* Creo el término independiente necesario. */
        double temp_b[m];
        for (j = 0; j < m; j++) 
            temp_b[j] = (j == i) ? 1.0 : 0.0;

        /* Copio la matriz de Vandermonde. */
        double **V_copy = (double**) calloc(m, sizeof(double*));
        for (j = 0; j < m; j++) { 
            fila = (double*) calloc(m, sizeof(double)); 
            V_copy[j] = fila;
            for (k = 0; k < m; k++) 
                V_copy[j][k] = V[j][k];
        }

        /* Triangulo. */
        elimGaus(m, V_copy, temp_b, tol);

        /* Soluciono. */
        double *temp_solution = triangSup(m, V_copy, temp_b);
        
        /* Relleno la columna i de la inversa. */
        if (temp_solution != NULL) {
            for (j = 0; j < m; j++) 
                V_inverse[j][i] = temp_solution[j];
            free(temp_solution);
        }

        /* Libero memoria de la matriz copiada. */
        for (j = 0; j < m; j++) 
            free(V_copy[j]);
        free(V_copy);
    }

    /* Calculamos el número de condición. */
    double norm_V = normMax(m, V);
    double norm_V_inv = normMax(m, V_inverse);
    double condition_number = norm_V * norm_V_inv;
    
    /* Libero memoria. */
    for (i = 0; i < m; i++) {
        free(V[i]); 
        free(V_inverse[i]);
    }
    free(V);
    free(V_inverse);

    return condition_number;
}