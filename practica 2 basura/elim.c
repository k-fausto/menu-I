/**
 * Karim Boujana Marcucci.
 */

#include <stdlib.h>
#include <math.h> 

int pivot(int n, double **matA, int k) {
    int i, max_index = k;
    double max_valor = fabs(matA[k][k]);  /* Valor máximo inicial */

    /* Buscamos en las filas desde k hasta n-1 */
    for (i = k + 1; i < n; i++) {
        /* Si encontramos un valor absoluto mayor, actualizamos */
        if (fabs(matA[i][k]) > max_valor) {
            max_index = i;
            max_valor = fabs(matA[i][k]);
        }
    }

    return max_index;
}


int elimGaus(int n, double **a, double *b, double tol) {
    int i, j, k, l;
    int p = 0;  /* Contador de intercambios */
    double multiplicador, temp_b;
    double *temp_fila = NULL;

    /* Procesamos cada columna desde 0 hasta n-1 */
    for (i = 0; i < n - 1; i++) {
        /* Encontramos el pivote maximal para la columna i */
        k = pivot(n, a, i);

        /* Verificamos si el pivote es demasiado pequeño */
        if (fabs(a[k][i]) < tol) {
            return -1;  /* Sistema singular */
        }
        
        /* Intercambiamos filas si es necesario */
        if (i != k) {
            p++;
            /* Intercambiamos filas de la matriz */
            temp_fila = a[i];
            a[i] = a[k];
            a[k] = temp_fila;
            
            /* Intercambiamos elementos del vector b */
            temp_b = b[i];
            b[i] = b[k];
            b[k] = temp_b;
        }

        /* Eliminación para las filas debajo de la fila i */
        for (j = i + 1; j < n; j++) {
            /* Calculamos el multiplicador */
            multiplicador = -a[j][i] / a[i][i];
            
            /* Actualizamos los elementos de la fila j */
            for (l = i; l < n; l++) {
                a[j][l] = a[j][l] + multiplicador * a[i][l];
            }
            
            /* Actualizamos el vector b */
            b[j] = b[j] + multiplicador * b[i];
        }
    }

    /* Verificamos el último elemento diagonal */
    if (fabs(a[n-1][n-1]) < tol) {
        return -1;  /* Sistema singular */
    }

    return p;
}
