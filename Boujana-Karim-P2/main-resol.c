/**
 * Karim Boujana Marcucci.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *triangSup(int n, double **matU, double *b);
int elimGaus(int n, double **a, double *b, double tol);
int pivot(int n, double **matA, int k);

int main(void) {
    char nombre_archivo_entrada[100];
    char nombre_archivo_salida[100];
    FILE *archivo_entrada, *archivo_salida;
    int dimension, i, j, k;
    double tolerancia;
    double norma_max_A = 0, norma_max_Axb = 0, norma_max_x = 0;

    /* Leemos el nombre del archivo de entrada */
    printf("Introduce el nombre del archivo de entrada: ");
    scanf("%99s", nombre_archivo_entrada);

    /* Intentamos abrir el archivo de entrada */
    archivo_entrada = fopen(nombre_archivo_entrada, "r");
    if (archivo_entrada == NULL) {
        printf("Error: No se puede abrir el archivo %s\n", nombre_archivo_entrada);
        return 1;
    }

    /* Leemos la dimensión del sistema */
    if (fscanf(archivo_entrada, "%d", &dimension) != 1) {
        printf("Error: No se pudo leer la dimensión del sistema.\n");
        fclose(archivo_entrada);
        return 1;
    }

    /* Reservamos memoria para la matriz del sistema y el vector independiente */
    double **sistema = (double **)malloc(dimension * sizeof(double *));
    double *b = (double *)malloc(dimension * sizeof(double));
    for (i = 0; i < dimension; i++) {
        sistema[i] = (double *)malloc(dimension * sizeof(double));
    }

    /* Leemos la matriz de coeficientes y el vector independiente */
    for (i = 0; i < dimension; i++) {
        /* Leemos los coeficientes de la fila i */
        for (j = 0; j < dimension; j++) {
            if (fscanf(archivo_entrada, "%lf", &sistema[i][j]) != 1) {
                printf("Error leyendo el coeficiente [%d][%d] del sistema.\n", i, j);
                /* Liberamos memoria antes de salir */
                for (k = 0; k < dimension; k++) free(sistema[k]);
                free(sistema);
                free(b);
                fclose(archivo_entrada);
                return 1;
            }
            /* Actualizamos la norma máxima de A */
            if (fabs(sistema[i][j]) > norma_max_A) {
                norma_max_A = fabs(sistema[i][j]);
            }
        }
        
        /* Leemos el término independiente de la fila i */
        if (fscanf(archivo_entrada, "%lf", &b[i]) != 1) {
            printf("Error leyendo el término independiente b[%d].\n", i);
            for (k = 0; k < dimension; k++) free(sistema[k]);
            free(sistema);
            free(b);
            fclose(archivo_entrada);
            return 1;
        }
    }

    /* Leemos la tolerancia */
    if (fscanf(archivo_entrada, "%le", &tolerancia) != 1) {
        printf("Error leyendo la tolerancia.\n");
        for (i = 0; i < dimension; i++) free(sistema[i]);
        free(sistema);
        free(b);
        fclose(archivo_entrada);
        return 1;
    }

    /* Leemos el nombre del archivo de salida */
    if (fscanf(archivo_entrada, "%s", nombre_archivo_salida) != 1) {
        printf("Error leyendo el nombre del archivo de salida.\n");
        for (i = 0; i < dimension; i++) free(sistema[i]);
        free(sistema);
        free(b);
        fclose(archivo_entrada);
        return 1;
    }

    /* Cerramos el archivo de entrada */
    fclose(archivo_entrada);

    /* Resolvemos el sistema usando eliminación Gaussiana */
    double *solucion;
    if (elimGaus(dimension, sistema, b, tolerancia) == -1) {
        printf("Sistema irresoluble.\n");
        for (i = 0; i < dimension; i++) free(sistema[i]);
        free(sistema);
        free(b);
        return 1;
    }
    
    /* Resolvemos el sistema triangular superior */
    solucion = triangSup(dimension, sistema, b);

    /* Abrimos el archivo de salida */
    archivo_salida = fopen(nombre_archivo_salida, "w");
    if (archivo_salida == NULL) {
        printf("Error: No se pudo crear el archivo %s\n", nombre_archivo_salida);
        for (i = 0; i < dimension; i++) free(sistema[i]);
        free(sistema);
        free(b);
        free(solucion);
        return 1;
    }

    /* Calculamos la norma máxima de Ax - b */
    for (i = 0; i < dimension; i++) {
        double temp = 0.0;
        for (j = 0; j < dimension; j++) {
            temp += sistema[i][j] * solucion[j];
        }
        temp -= b[i];
        if (fabs(temp) > norma_max_Axb) {
            norma_max_Axb = fabs(temp);
        }
    }

    /* Escribimos la solución y calculamos la norma máxima de x */
    for (i = 0; i < dimension; i++) {
        if (fabs(solucion[i]) > norma_max_x) {
            norma_max_x = fabs(solucion[i]);
        }
        if (i != dimension - 1) {
            fprintf(archivo_salida, "%le ", solucion[i]);
        } else {
            fprintf(archivo_salida, "%le\n", solucion[i]);
        }
    }

    /* Escribimos las normas en el archivo de salida */
    fprintf(archivo_salida, "Norma máxima de A: %le\n", norma_max_A);
    fprintf(archivo_salida, "Norma máxima de Ax-b: %le\n", norma_max_Axb);
    fprintf(archivo_salida, "Norma máxima de x: %le", norma_max_x);

    /* Cerramos el archivo de salida */
    fclose(archivo_salida);

    /* Liberamos la memoria */
    for (i = 0; i < dimension; i++) free(sistema[i]);
    free(sistema);
    free(b);
    free(solucion);

    printf("Solución guardada en %s\n", nombre_archivo_salida);
    return 0;
}