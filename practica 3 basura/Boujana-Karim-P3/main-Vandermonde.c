/**
 * Karim Boujana Marcucci.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *triangSup(int n, double **matU, double *b);
int elimGaus(int n, double **a, double *b, double tol);
int pivot(int n, double **matA, int k);
double normMax(int m, double **matA);
double condV(int m, double tol);

int main(void) {

    int mmin, mmax, dif, i;
    double tol, condition_number;
    FILE* fptr;
    fptr = fopen("cond.txt", "w");
    if (fptr == NULL) {
        printf("Error: No se pudo abrir el archivo para escritura.\n");
        return -1;
    }

    printf("Introduce una dimension minima: ");
    scanf("%d", &mmin);
    printf("Introduce una dimension maxima: ");
    scanf("%d", &mmax);
    printf("Introduce una tolerancia: ");
    scanf("%le", &tol);
    dif = mmax - mmin;

    if (mmin < 0 || mmax < 0 || dif < 1) return -1;
    for (i = mmin+1; i < mmax; i++) {
        condition_number = condV(i, tol);
        fprintf(fptr, "%d %.30le\n", i, log10(condition_number));
    }

    printf("Resultados guardados en: cond.txt");
    fclose(fptr);
    
    return 0;
}