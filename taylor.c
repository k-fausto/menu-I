#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
    
    const double E = exp(1);
    int i = 0;
    int k = 1;
        
    /* Cálculos de los n apropiados para el apartado a).
    

    while (n_factorial < E/pow(10, -8)) {

        n_factorial *= ++n;
        printf("Factorial de %d vale %ld.\n", n, n_factorial);
        // Valor n+1 = 12.
    }

    n_factorial = 1;
    n = 1;

    while (n_factorial < 1/(pow(10, -8)*E)) {

        n_factorial *= ++n;
        printf("Factorial de %d vale %ld.\n", n, n_factorial);
        // Valor: n+1 = 11
        
        
        }
    */

   /*   Voy a escribir un algoritmo que para una x0 y un épsilon de tolerancia, puede calcular el grado correcto para el polinomio de Taylor
        y usarlo para calcular una aproximación. Como los valores de x son cercanos a x0, los describiré con:
        x = x0 + epsilon con -1 <= epsilon <= 1.*/

    int pruebas[] = {3, 6, -6, 5};
    for (i = 0; i < 5; i++){

        int x0 = pruebas[i];
        double epsilon = ((double) rand() / (double) RAND_MAX);
        double x = x0 + epsilon;
        const double precision = 1e-8;
        double aprox = 1;
        printf("\nCalculemos e^x con el polinomio de Taylor, centrado en x0 = %d, con x = %d + %f, y con una precision de %le\n", x0, x0, epsilon, precision);

        /* Para calcular una n apropiada, necesitamos que se cumpla la inecuación descrita en el word. */
        long int n = 1;
        long int n_factorial = 1;

        while ((exp(x0)/(n_factorial))*pow(epsilon, n) > precision) n_factorial *= ++n;
        
        
        printf("El factorial de %ld+1 vale %ld, lo cual cumple la desigualdad.\n", n-1, n_factorial);
        printf("Se ve que %le es menor que %le.\n", (exp(x0)/(n_factorial))*pow(epsilon, n), precision);

        /*  Con esto, tenemos el grado que necesitábamos para calcular el polinomio.
            Solo queda hacer la aproximación haciendo uso de la serie de Taylor. */

        
        long int temp_k_factorial = 1;
        for (k = 1; k <= n; k++) {
            temp_k_factorial *= k;
            aprox += pow(epsilon, k)/(temp_k_factorial);
        }
        aprox *= exp(x0);

        printf("Nos da que el valor de la aproximacion es %.16le, el valor real es %.16le.\n", aprox, exp(x));
        printf("El error absoluto cometido es %le y su error relativo es del %le%%.\n", fabs(aprox-exp(x)), fabs(aprox-exp(x))/exp(x));

        printf("\n");

    }
    
    
    
}
