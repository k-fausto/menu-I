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
    double theta = 1.0, s = 0.0, c = 0.0, cpu_time_spent;
    clock_t start, end;
    int n = 3200, i = 0, j = 0;
    FILE *fptr;
    fptr = fopen("time.dat", "w");

    /*
    
    printf("Introduce un angulo (theta): \n");
    scanf("%lf", &theta);

    printf("Introduce la dimension deseada: \n");
    scanf("%d", &n);
    */

    if (theta  < (5.0*PI/16.0) || theta > PI/2.0) printf("Valor de theta invalido.\n");
    else if (n < 0) printf("Valor de n invalido.\n");

    else {

        for (theta = 5.0*PI/16.0; theta < PI/2; theta += PI/512) {

            /**
             * Calculamos el seno, conseno y creamos la matriz Kn(theta).
             */
            s = sin(theta);
            c = cos(theta);
            
            double **K = calloc(n, sizeof(double*));
            if (K == NULL) { perror("Calloc matriu K"); return 1;}
            double e[n];
            double temp_s = 1;
            
            /**
             * En este bucle, en paralelo rellenaré el vector e de ceros,
             * y rellenaré la matriz, con unos, y siguiendo la estructura que se muestra en el ejercicio.
             * Como nuestra función solo se fijará en los valores triangulares superiores, me da igual qué rellene 
             * en los triangulares inferiores.
             */
            for (i = 0; i < n; i++) {
                K[i] = calloc(n, sizeof(double));
                if (K[i] == NULL) { perror("Calloc fila de matriu K"); return 1;}
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
            start = clock();
            double *solution = triangSup(n, K, e);
    
            /* Descomentar para comprobar la solución.
            
            if (solution != NULL) {
                
                printf("SOLUCIOOOOOOOOON -------------------------------------\n");
                for (j = 0; j < n; j++) printf("%8.4le ", solution[j]);
            }
            */
               
            end = clock();
            free(solution); 
    
    
            /* Limpiamos la memoria de la matriz. */
            for (i = 0; i < n; i++) free(K[i]);
            free(K);
    
            /* Mostramos por pantalla el tiempo de ejecución. */
    
            cpu_time_spent = ((double) (end - start)) / CLOCKS_PER_SEC;
            fprintf(fptr, "%.30le %.30le\n", theta, cpu_time_spent);
            /*printf("La solucion tardo: %le segundos en ejecutarse.\n", cpu_time_spent);*/
    
            /* Prueba de que funciona. -----> Checked. 
            double e_prueba[3] = {1, 3, -1};
            double mat_prueba[3][3] = {{3, 1, 2}, {0, -1, 1}, {0, 0, 2}};
    
            double *mat_ptrs[3];
            for (i = 0; i < 3; i++) {
                mat_ptrs[i] = mat_prueba[i]; 
            }
    
            double *solution_prueba = triangSup(3, mat_ptrs, e_prueba);
    
            if (solution_prueba != NULL) {
                
                printf("SOLUCIOOOOOOOOON -------------------------------------\n");
                for (j = 0; j < n; j++) printf("%8.4le ", solution_prueba[j]);
                free(solution_prueba); 
            }
            */

        }

    }

    fclose(fptr);
    return 0;
}