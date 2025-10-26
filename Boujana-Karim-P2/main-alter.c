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

    int dimension, i, j;
    double tolerancia = 1e-16;
    FILE* archivo_salida;

    /* Resolvamos la matriz H. */
    
    double norma_max_H = 0, norma_max_Hxb = 0, norma_max_x = 0;
    

    /* Leemos la dimensión del sistema */
    printf("Introduce la dimensión del sistema del problema 1: ");
    scanf("%d", &dimension);

    /* Reservamos memoria para la matriz del sistema y el vector independiente */
    double **H = (double **)malloc(dimension * sizeof(double *));
    double *Hb = (double *)calloc(dimension, sizeof(double));
    for (i = 0; i < dimension; i++) {
        H[i] = (double *)malloc(dimension * sizeof(double));
    }

    /* Rellenamos la matriz con los valores y calculamos la norma máxima de H. */
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            H[i][j] = 1.0/(i+j+1);
            Hb[i] += 1.0/(i+j+1);
            if (norma_max_H < fabs(H[i][j])) norma_max_H = fabs(H[i][j]);
        }
    }

    /* Resolvemos el sistema usando eliminación Gaussiana */
    double *solucion_H;
    if (elimGaus(dimension, H, Hb, tolerancia) == -1) {
        printf("Sistema irresoluble.\n");
        for (i = 0; i < dimension; i++) free(H[i]);
        free(H);
        free(Hb);
        return 1;
    }
    solucion_H = triangSup(dimension, H, Hb);

    /* Creamos el archivo de salida */
    archivo_salida = fopen("problema1_solution.txt", "w");
    if (archivo_salida == NULL) {
        printf("Error: No se pudo crear el archivo.\n");
        for (i = 0; i < dimension; i++) free(H[i]);
        free(H);
        free(Hb);
        free(solucion_H);
        return 1;
    }

    /* Calculamos la norma máxima de Hx - b */
    for (i = 0; i < dimension; i++) {
        double temp = 0.0;
        for (j = 0; j < dimension; j++) {
            temp += H[i][j] * solucion_H[j];
        }
        temp -= Hb[i];
        if (fabs(temp) > norma_max_Hxb) {
            norma_max_Hxb = fabs(temp);
        }
    }

    /* Escribimos la solución y calculamos la norma máxima de x */
    for (i = 0; i < dimension; i++) {
        if (fabs(solucion_H[i]) > norma_max_x) norma_max_x = fabs(solucion_H[i]);
        
        if (i != dimension - 1) {
            fprintf(archivo_salida, "%le ", solucion_H[i]);
        } else {
            fprintf(archivo_salida, "%le\n", solucion_H[i]);
        }
    }

    /* Escribimos las normas en el archivo de salida */
    fprintf(archivo_salida, "Norma máxima de H: %le\n", norma_max_H);
    fprintf(archivo_salida, "Norma máxima de Hx-b: %le\n", norma_max_Hxb);
    fprintf(archivo_salida, "Norma máxima de x: %le", norma_max_x);


    /* Cerramos el archivo de salida. */
    fclose(archivo_salida);


    /* Liberamos la memoria */
    for (i = 0; i < dimension; i++) free(H[i]);
    free(H);
    free(Hb);
    free(solucion_H);

    /* PROBLEMA 2: Matriz A con a_ij = min(i,j)/max(i,j) para n=10, b último vector canónico */
    int n2;
    /* Leemos la dimensión del sistema */
    printf("Introduce la dimensión del sistema del problema 2: ");
    scanf("%d", &n2);

    double **A = (double **)malloc(n2 * sizeof(double *));
    double *b2 = (double *)calloc(n2, sizeof(double));
    for (i = 0; i < n2; i++) {
        A[i] = (double *)malloc(n2 * sizeof(double));
    }
    
    b2[n2-1] = 1.0;  /* Último vector canónico */
    
    /* Construimos la matriz A original */
    for (i = 0; i < n2; i++) {
        for (j = 0; j < n2; j++) {
            if (i <= j) A[i][j] = (double)(i+1)/(j+1);
            else A[i][j] = (double)(j+1)/(i+1);
        }
    }

    archivo_salida = fopen("problema2_lambda_solutions.txt", "w");
    if (archivo_salida == NULL) {
        printf("Error: No se pudo crear el archivo.\n");
        for (i = 0; i < n2; i++) free(A[i]);
        free(A);
        free(b2);
        return 1;
    }

    /* Estudiamos la evolución para lambda entre -10 y 10 */
    double lambda;
    int num_intercambios;
    
    for (lambda = -10.0; lambda <= 10.0; lambda += 0.5) {
        /* Creamos copia de A modificada con lambda: A(λ) = A - λI */
        double **A_lambda = (double **)malloc(n2 * sizeof(double *));
        double *b2_copy = (double *)malloc(n2 * sizeof(double));
        for (i = 0; i < n2; i++) {
            A_lambda[i] = (double *)malloc(n2 * sizeof(double));
            for (j = 0; j < n2; j++) {
                if (i == j) 
                    A_lambda[i][j] = A[i][j] - lambda;  /* Restamos lambda en la diagonal */
                else 
                    A_lambda[i][j] = A[i][j];
            }
            b2_copy[i] = b2[i];
        }

        /* Resolvemos el sistema */
        double *solucion2;
        num_intercambios = elimGaus(n2, A_lambda, b2_copy, tolerancia);
        
        if (num_intercambios == -1) {
            fprintf(archivo_salida, "Lambda: %6.2f - Sistema singular\n", lambda);
        } else {
            solucion2 = triangSup(n2, A_lambda, b2_copy);
            fprintf(archivo_salida, "Lambda: %6.2f, Intercambios: %d, Solucion: ", lambda, num_intercambios);
            for (i = 0; i < n2; i++) {
                fprintf(archivo_salida, "%le ", solucion2[i]);
            }
            fprintf(archivo_salida, "\n");
            free(solucion2);
        }

        /* Liberamos memoria de las copias */
        for (i = 0; i < n2; i++) free(A_lambda[i]);
        free(A_lambda);
        free(b2_copy);
    }

    fclose(archivo_salida);

    /* Liberamos memoria de la matriz original */
    for (i = 0; i < n2; i++) free(A[i]);
    free(A);
    free(b2);

    /* PROBLEMA 20: Sistema Bx = c */
    int n3 = 4;
    double B[4][4] = {
        {1, -1, 2, 1},
        {2, 5, 5, -1},
        {3, 3, 7, 2},
        {4, 8, -6, 1}
    };
    double c[4] = {0, 7, 1, 2};

    double **B_mat = (double **)malloc(n3 * sizeof(double *));
    double *c_vec = (double *)malloc(n3 * sizeof(double));
    for (i = 0; i < n3; i++) {
        B_mat[i] = (double *)malloc(n3 * sizeof(double));
        for (j = 0; j < n3; j++) {
            B_mat[i][j] = B[i][j];
        }
        c_vec[i] = c[i];
    }

    double *solucion3;
    if (elimGaus(n3, B_mat, c_vec, tolerancia) == -1) {
        printf("Sistema 20 irresoluble.\n");
    } else {
        solucion3 = triangSup(n3, B_mat, c_vec);
        archivo_salida = fopen("problema20_solution.txt", "w");
        for (i = 0; i < n3; i++) {
            if (i != n3-1) fprintf(archivo_salida, "%le ", solucion3[i]);
            else fprintf(archivo_salida, "%le\n", solucion3[i]);
        }
        fclose(archivo_salida);
        free(solucion3);
    }

    for (i = 0; i < n3; i++) free(B_mat[i]);
    free(B_mat);
    free(c_vec);

    /* PROBLEMA 22: Matriz simétrica con todos los términos independientes 1 */
    int n4 = 4;
    double D[4][4] = {
        {1, 2, -1, 3},
        {2, 8, 4, 2},
        {-1, 4, 11, -5},
        {3, 2, -5, 38}
    };
    double d[4] = {1, 1, 1, 1};

    double **D_mat = (double **)malloc(n4 * sizeof(double *));
    double *d_vec = (double *)malloc(n4 * sizeof(double));
    for (i = 0; i < n4; i++) {
        D_mat[i] = (double *)malloc(n4 * sizeof(double));
        for (j = 0; j < n4; j++) {
            D_mat[i][j] = D[i][j];
        }
        d_vec[i] = d[i];
    }

    double *solucion4;
    if (elimGaus(n4, D_mat, d_vec, tolerancia) == -1) {
        printf("Sistema 22 irresoluble.\n");
    } else {
        solucion4 = triangSup(n4, D_mat, d_vec);
        archivo_salida = fopen("problema22_solution.txt", "w");
        for (i = 0; i < n4; i++) {
            if (i != n4-1) fprintf(archivo_salida, "%le ", solucion4[i]);
            else fprintf(archivo_salida, "%le\n", solucion4[i]);
        }
        fclose(archivo_salida);
        free(solucion4);
    }

    for (i = 0; i < n4; i++) free(D_mat[i]);
    free(D_mat);
    free(d_vec);

    /* PROBLEMA 25: Matriz 3x3. */
    int n5 = 3;
    double E[3][3] = {
        {1, -1, 2},
        {-1, 0.5, -1},
        {2, -1, 4}
    };
    double e[3] = {-1, 3, 2}; 

    double **E_mat = (double **)malloc(n5 * sizeof(double *));
    double *e_vec = (double *)malloc(n5 * sizeof(double));
    for (i = 0; i < n5; i++) {
        E_mat[i] = (double *)malloc(n5 * sizeof(double));
        for (j = 0; j < n5; j++) {
            E_mat[i][j] = E[i][j];
        }
        e_vec[i] = e[i];
    }

    double *solucion5;
    if (elimGaus(n5, E_mat, e_vec, tolerancia) == -1) {
        printf("Sistema 25 irresoluble.\n");
    } else {
        solucion5 = triangSup(n5, E_mat, e_vec);
        archivo_salida = fopen("problema25_solution.txt", "w");
        for (i = 0; i < n5; i++) {
            if (i != n5-1) fprintf(archivo_salida, "%le ", solucion5[i]);
            else fprintf(archivo_salida, "%le\n", solucion5[i]);
        }
        fclose(archivo_salida);
        free(solucion5);
    }

    for (i = 0; i < n5; i++) free(E_mat[i]);
    free(E_mat);
    free(e_vec);

    /* PROBLEMA 26: Matriz triangular inferior con vector independiente potencias de 1/2. */
    int n6;
    printf("Introduce la dimensión para el problema 26: ");
    scanf("%d", &n6);

    double **F = (double **)malloc(n6 * sizeof(double *));
    double *f = (double *)malloc(n6 * sizeof(double));
    for (i = 0; i < n6; i++) {
        F[i] = (double *)malloc(n6 * sizeof(double));
        for (j = 0; j < n6; j++) {
            if (i == j) F[i][j] = 1.0;
            else if (i > j) F[i][j] = -1.0;
            else F[i][j] = 0.0;
        }
        f[i] = pow(0.5, n6 - i - 1);  /* y_i = (1/2)^(n-i) */
    }

    double **F_copy = (double **)malloc(n6 * sizeof(double *));
    double *f_copy = (double *)malloc(n6 * sizeof(double));
    for (i = 0; i < n6; i++) {
        F_copy[i] = (double *)malloc(n6 * sizeof(double));
        for (j = 0; j < n6; j++) {
            F_copy[i][j] = F[i][j];
        }
        f_copy[i] = f[i];
    }

    double *solucion6;
    if (elimGaus(n6, F_copy, f_copy, tolerancia) == -1) {
        printf("Sistema 26 irresoluble.\n");
    } else {
        solucion6 = triangSup(n6, F_copy, f_copy);
        archivo_salida = fopen("problema26_solution.txt", "w");
        for (i = 0; i < n6; i++) {
            if (i != n6-1) fprintf(archivo_salida, "%le ", solucion6[i]);
            else fprintf(archivo_salida, "%le\n", solucion6[i]);
        }
        fclose(archivo_salida);
        free(solucion6);
    }

    for (i = 0; i < n6; i++) free(F[i]);
    for (i = 0; i < n6; i++) free(F_copy[i]);
    free(F);
    free(F_copy);
    free(f);
    free(f_copy);

    return 0;

}