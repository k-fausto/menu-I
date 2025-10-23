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
  
  /* Inicializamos variables. */
  int i, j, k, l, temp_b, p;
  double m_i;
  double *temp = NULL;

  /* Iremos eliminando fila a fila, comenzando por la 0. */
  for (i = 0; i < n; i++) {

    /* Encontramos el pivote maximal. */
    k = pivot(n, a, i);

    /* Si el pivote es menor que la tolerancia, consideraremos el valor cero. En este caso, consideramos que el sistema es irresoluble. */
    if (fabs(a[k][i]) < fabs(tol)) return -1; 
    
    /* En caso contrario, intercambiamos las filas y el término independiente. */
    if (i != k){
      p++;
      temp = a[i];
      a[i] = a[k];
      a[k] = temp;
      temp_b = b[i];
      b[i] = b[k];
      b[k] = temp_b;
    }

    /* Una vez tenemos el pivote, restemos entre la cantidad necesaria a las filas inferiores. */

    for (j = i+1; j < n; j++) { /* Acedo a las fila j por debajo de la fila i. */
      
      m_i = -(a[i][i])/(a[j][i]);
      
      /* Accedo a cada elemento l de la fila j y lo actualizo. */
      for (l = i+1; l < n; l++) {a[j][l] = m_i * a[j][l] + a[i][l];
      b[j] = m_i * b[j] + b[i];
        
      }

    }

  }

  return p;
  
}