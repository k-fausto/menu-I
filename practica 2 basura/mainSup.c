/**
 * Karim Boujana Marcucci.
 */

#include "triang.c"
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void) {

    /**
     * Inicializamos variables y obtenemos los valores deseados, comprobando que sean correctos.
     */
    const double PI = acos(-1.0);
    double theta = 1.0, s = 0.0, c = 0.0;
    int n = 800, i = 0, j = 0;

    /*
    
    printf("Introduce un angulo (theta): \n");
    scanf("%lf", &theta);

    printf("Introduce la dimension deseada: \n");
    scanf("%d", &n);
    */

    if (theta  < (5.0*PI/16.0) || theta > PI/2.0) printf("Valor de theta invalido.\n");
    else if (n < 0) printf("Valor de n invalido.\n");

    else {
        
       

        /**
         * Calculamos el seno, conseno y creamos la matriz Kn(theta).
         */
        s = sin(theta);
        c = cos(theta);
        
        double **K = malloc(n * sizeof(double*));
        double e[n];
        double temp_s = 1;
        
        /**
         * En este bucle, en paralelo rellenaré el vector e de ceros,
         * y rellenaré la matriz, con unos, y siguiendo la estructura que se muestra en el ejercicio.
         * Como nuestra función solo se fijará en los valores triangulares superiores, me da igual qué rellene 
         * en los triangulares inferiores.
         */
        for (i = 0; i < n; i++) {
            K[i] = malloc(n * sizeof(double));
            e[i] = 0;
            if (i == n-1) e[i] = 1;
            for (j = 0; j < n; j++) {

                K[i][j] = 1;
                if (i < j) K[i][j] *= -c;
                K[i][j] *= temp_s; 

            }
            temp_s *= s;
        }

        /* Printear la matrix si queremos.
        printf("\nMatrix Kn(theta):\n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                printf("%8.4le ", K[i][j]);
            }
            printf("\n");
        }
            */

        /**
         * Calculamos el tiempo de ejecución.
         */
        clock_t begin = clock();
        double *solution = triangSup(n, K, e);

        if (solution != NULL) {
            /*
            printf("SOLUCIOOOOOOOOON -------------------------------------\n");
            for (j = 0; j < n; j++) printf("%8.4le ", solution[j]);
            */
            free(solution); 
        }

        clock_t end = clock();

        /* Limpiamos la memoria de la matriz. */
        for (i = 0; i < n; i++) free(K[i]);
        free(K);

        /* Mostramos por pantalla el tiempo de ejecución. */

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("La solucion tardo: %le segundos en ejecutarse.\n", time_spent);

    }

    return 0;
}