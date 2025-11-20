/**
 * Karim Boujana Marcucci.
 */

 #include <stdlib.h>
 #include <math.h>

double *triangSup(int n, double **matU, double *b) {
    
    /* Inicializamos el vector solución y variables temporales */
    double *x = malloc(n * sizeof(double));
    double temp;
    int i, j;

    /* Resolvemos desde la última ecuación hasta la primera */
    for (i = n - 1; i >= 0; i--) {
        temp = 0.0;
        
        /**
         * Sumamos todos los términos a la derecha del elemento diagonal:
         * temp = Σ (matU[i][j] * x[j]) para j desde i+1 hasta n-1
         */
        for (j = i + 1; j < n; j++) {
            temp += matU[i][j] * x[j];
        }
        
        /* Verificamos que el elemento diagonal no sea cero */
        if (fabs(matU[i][i]) < 1e-15) {
            free(x);
            return NULL;  /* Matriz singular */
        }
        
        /* Calculamos x[i] = (b[i] - temp) / matU[i][i] */
        x[i] = (b[i] - temp) / matU[i][i];
    }

    /* Devolvemos el vector solución */
    return x;   
}
