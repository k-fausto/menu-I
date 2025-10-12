/**
 * Karim Boujana Marcucci.
 */

 #include <stdlib.h>

double * triangSup (int n , double ** matU , double *b) {
    
    /*Inicializo el vector que retornameros, una variable temporal y los indices.*/
    double *x = malloc(n * sizeof(double));
    double temp = 0.0;
    int i, j;

    for (i = n-1; i >= 0; i--) {

        /**
         * Sumamos todos los elementos a la derecha de aii * xii con sus respectivas solcuiones, y luego lo pasamos restando, 
         * para dividirlo entre el coeficiente de xi.
         */
        for (j = n-1; j > i; j--) temp += x[j] * matU[i][j];
        x[i] = (b[i] - temp) / matU[i][i];

    }

    /* Devolvemos el vector solucion. */
    return x;   

}