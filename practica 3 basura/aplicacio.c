/**
 * Karim Boujana Marcucci.
 */

#include <stdlib.h>
#include <math.h> 
#include <stdio.h>

void dif_div (int n , double *x , double *f);
double hornerNew (int n , double *b , double *x , double z);
double f_1(double x);
double f_2(double x);
double f_3(double x);
double f_4(double x);

int main(void) {
    int n = 0, i;
    FILE *fptr_1, *fptr_2, *fptr_3, *fptr_4;
    
    printf("Introduce el grado del polinomio interpolador: ");
    scanf("%d", &n);
    if (n < 0) return -1;

    /* CORRECTED: Fixed array initialization */
    double x[n+1];
    for (i = 0; i <= n; i++) {
        x[i] = -1.0 + (2.0 * i) / n;
    }

    /* Initialize function values */
    double f1[n+1];
    double f2[n+1];
    double f3[n+1];
    double f4[n+1];

    for (i = 0; i <= n; i++) {
        f1[i] = f_1(x[i]);
        f2[i] = f_2(x[i]);
        f3[i] = f_3(x[i]);
        f4[i] = f_4(x[i]);
    }

    /* Compute divided differences */
    dif_div(n, x, f1);
    dif_div(n, x, f2);
    dif_div(n, x, f3);
    dif_div(n, x, f4);

    /* Evaluate and plot polynomials */
    fptr_1 = fopen("f1.dat", "w");
    fptr_2 = fopen("f2.dat", "w");
    fptr_3 = fopen("f3.dat", "w");
    fptr_4 = fopen("f4.dat", "w");
    
    for (i = -100; i <= 100; i++) {
        double z = i / 100.0;
        fprintf(fptr_1, "%le %le %le\n", z, f_1(z), hornerNew(n, f1, x, z)-1);
        fprintf(fptr_2, "%le %le %le\n", z, f_2(z), hornerNew(n, f2, x, z));
        fprintf(fptr_3, "%le %le %le\n", z, f_3(z), hornerNew(n, f3, x, z));
        fprintf(fptr_4, "%le %le %le\n", z, f_4(z), hornerNew(n, f4, x, z));
    }

    fclose(fptr_1);
    fclose(fptr_2);
    fclose(fptr_3);
    fclose(fptr_4);
    return 0;
}