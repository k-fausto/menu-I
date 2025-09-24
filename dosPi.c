#include <stdio.h>
#include <math.h>

int main(void) {
    // Haremos t comprobaciones.
    int t = 15;

    /**
     * Tabla de resultados de la primera sucesión, sk, con precisión simple.
     */
    float PI = acosf(-1.0);
    float sk_0, sk_1, er;
    int k = 0;
    sk_0 = sqrtf(2);

    printf("============================================================================\n");
    printf("||\tAproximacion de pi usando sk, y precision simple.\n");
    printf("============================================================================\n");

    for (int i = 3; i <= t ; i++) {
        k = pow(2,i);
        sk_1 = sqrtf(2 - sqrtf(4 - powf(sk_0, 2)));
        er = fabsf((sk_1 * k - 2 * PI) / (2 * PI)); // Corregidos los paréntesis

        printf("||\tNumero de vertices: %7d \t ||\tValor de la aproximacion: %le \t || \tError relativo: %le%%.\n", k/2, (double)(sk_1 * k), (double)(er * 100)); // Cast a double para %le
        sk_0 = sk_1;
    }

    printf("============================================================================\n\n");
    
    /**
     * Tabla de resultados con precisión doble.
     */
    printf("============================================================================\n");
    printf("||\tAproximacion de pi usando sk, y precision doble.\n");
    printf("============================================================================\n");

    double d_PI = acos(-1.0);
    double d_sk_0, d_sk_1, d_er;
    d_sk_0 = sqrt(2);

    for (int i = 3; i <= t ; i++) {
        k = pow(2,i);
        d_sk_1 = sqrt(2 - sqrt(4 - pow(d_sk_0, 2)));
        d_er = fabs((d_sk_1 * k - 2 * d_PI) / (2 * d_PI)); // Corregidos los paréntesis

        printf("||\tNumero de vertices: %7d \t ||\tValor de la aproximacion: %le \t || \tError relativo: %le%%.\n", k/2, d_sk_1 * k, d_er * 100);
        d_sk_0 = d_sk_1;
    }
    printf("============================================================================\n\n");

    return 0;
}