/**
 * Karim Boujana Marcucci.
 */

#include <math.h> 

double normMax(int m, double **matA) {
    /**
     * Clalcula la norma máxima de una matriz.
     */
    double maxRowSum = 0.0;
    int i, j;

    for (i = 0; i < m; i++) {
        /* Sumo todos los elementos de la fila en valor absoluto, y me voy quedando con los máximos.*/
        double rowSum = 0.0;
        for (j = 0; j < m; j++) rowSum += fabs(matA[i][j]);
        if (rowSum > maxRowSum) maxRowSum = rowSum;
        
    }

    return maxRowSum;


}