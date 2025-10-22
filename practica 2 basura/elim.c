/**
 * Karim Boujana Marcucci.
 */

  #include <stdlib.h>
  #include <math.h> 

  int pivot (int n , double ** matA , int k) {

    /* Inicializamos variables. */
    int i, max_index = k;
    double max_pivot = matA[k][k]; /* Asumo la primera un máximo. */


    for (i = k; i < n; i++) {

        /* En el caso que tengamos un pivote más grande en valor absoluto, lo seleccionamos: */
        if (fabs(max_pivot) < fabs(matA[i][k])) {
            max_index = i;
            max_pivot = matA[i][k];
        }

    }

    return max_index;

  }

  int elimGaus (int n , double **a , double *b , double tol ) {
    
    

  }