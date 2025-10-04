/**
 * Karim Boujana Marcucci.
 */

#include <stdio.h>
#include <math.h>

int main(void) {
    /* Haremos t comprobaciones.*/
    int t = 28;

    float acosf(float);
    float sqrtf(float);
    float powf(float, float);
    float fabsf(float);
    
    float PI = acosf(-1.0);
    double d_PI = acos(-1.0);
    int i = 3;
    int k = 4;

    /*Creemos el archivo que gnuplot leerá.*/

    FILE *f1, *f2, *f3, *f4, *f5;
    f1 = fopen("Sk_simple.dat", "w");
    f2 = fopen("Sk_doble.dat", "w");
    f3 = fopen("Ck_simple.dat", "w");
    f4 = fopen("Ck_doble.dat", "w");
    f5 = fopen("Sk_sin_cancelacion.dat", "w");

    /**
     * Tabla de resultados de la primera sucesión, sk, con precisión simple.
     */
    float sk_0, sk_1, er;
    
    sk_0 = sqrtf(2);

    printf("============================================================================\n");
    printf("||\tAproximacion de dos veces pi usando sk, y precision simple.\n");
    printf("============================================================================\n");

    for (i = 3; i <= t ; i++) {
        k *= 2;
        sk_1 = sqrtf(2 - sqrtf(4 - sk_0*sk_0));
        er = fabsf((sk_1 * k - 2 * PI) / (2 * PI)); 

        printf("||\tNumero de vertices: %7d \t ||\tValor de la aproximacion: %.20le \t || \tError relativo: %.20le%%.\n", 
            k/2, sk_1 * k, er * 100);
        sk_0 = sk_1;
        fprintf(f1, "%d %f\n", k/2, er*100);
    }

    printf("============================================================================\n\n");
    
    /**
     * Tabla de resultados con precisión doble.
     */
    printf("============================================================================\n");
    printf("||\tAproximacion de dos veces pi usando sk, y precision doble.\n");
    printf("============================================================================\n");

    
    double d_sk_0, d_sk_1, d_er;
    d_sk_0 = sqrt(2);

    k = 4;
    for (i = 3; i <= t ; i++) {
        k *= 2;
        d_sk_1 = sqrt(2 - sqrt(4 - d_sk_0 * d_sk_0));
        d_er = fabs((d_sk_1 * k - 2 * d_PI) / (2 * d_PI));

        printf("||\tNumero de vertices: %7d \t ||\tValor de la aproximacion: %.20le \t || \tError relativo: %.20le%%.\n", 
            k/2, d_sk_1 * k, d_er * 100);
        d_sk_0 = d_sk_1;
        fprintf(f2, "%d %le\n", k/2, d_er*100);
    }
    printf("============================================================================\n\n");
    
    
    
    /**
     * Tabla de resultados de la primera sucesión, ck, con precisión simple.
     */
    
    printf("============================================================================\n");
    printf("||\tAproximacion de dos veces pi usando ck, y precision simple.\n");
    printf("============================================================================\n");

    float ck;
    sk_0 = sqrtf(2);
    k = 4;
    
    for (i = 3; i <= t ; i++) {
        k *= 2;
        sk_1 = sqrtf(2 - sqrtf(4 - sk_0*sk_0));
        
        ck = (2*sk_1)/(sqrtf(4-sk_1*sk_1));
        
        er = fabsf((ck * k - 2 * PI) / (2 * PI)); 
        
        printf("||\tNumero de vertices: %7d \t ||\tValor de la aproximacion: %.20le \t || \tError relativo: %.20le%%.\n", k/2, ck * k, er * 100);
        sk_0 = sk_1;
        fprintf(f3, "%d %f\n", k/2, er*100);
    }
    
    printf("============================================================================\n\n");
    
    /**
     * Tabla de resultados con precisión doble.
     */
    printf("============================================================================\n");
    printf("||\tAproximacion de dos veces pi usando ck, y precision doble.\n");
    printf("============================================================================\n");
    
    double d_ck;
    d_sk_0 = sqrt(2);
    k = 4;
    
    for (i = 3; i <= t ; i++) {
        k *= 2;
        d_sk_1 = sqrt(2 - sqrt(4 - d_sk_0*d_sk_0));
        d_ck = (2*d_sk_1)/(sqrt(4 - d_sk_1*d_sk_1));
        d_er = fabs((d_ck * k - 2 * d_PI) / (2 * d_PI)); 
        
        printf("||\tNumero de vertices: %7d \t ||\tValor de la aproximacion: %.20le \t || \tError relativo: %.20le%%.\n", k/2, d_sk_1 * k, d_er * 100);
        d_sk_0 = d_sk_1;
        fprintf(f4, "%d %le\n", k/2, d_er*100);
    }
    printf("============================================================================\n\n");

    /*Con sk mejorado.*/
    printf("============================================================================\n");
    printf("||\tAproximacion de dos veces pi usando sk sin cancelacion, y precision doble.\n");
    printf("============================================================================\n");

    double sk = 0.0;
    k = 4;
    for (i = 2; i <= t; i++) {
        k *= 2;
        sk = 2.0 * sin(d_PI/k);
        d_er = fabs((sk * k - 2.0 * d_PI) / (2.0 * d_PI)); 

        printf("||\tNumero de vertices: %11d \t ||\tValor de la aproximacion: %.20le \t || \tError relativo: %.20le%%.\n", k, sk * k, d_er * 100);
        fprintf(f5, "%d %f\n", k, d_er*100);
    }

    printf("============================================================================\n\n");

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);

    return 0;
}
