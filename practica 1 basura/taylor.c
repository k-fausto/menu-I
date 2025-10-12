/**
 * Karim Boujana Marcucci.
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
    
    const double E = exp(1);
    const double precision = 1e-8;
    double aprox, epsilon, temp_epsilon, x;
    int i = 0, k = 1, x0;
    long int n_factorial = 1, n = 1;

    
    /* Cálculos de los n apropiados para el apartado a). */
    /*
    
    while (n_factorial < E/precision) n_factorial *= ++n;
    printf("\nSe necesita el factorial de %ld, que vale %ld para la precision deseada con x0 = 1.\n", n, n_factorial);
    
    n_factorial = 1;
    n = 1;
    
    while (n_factorial < 1/(precision*E)) n_factorial *= ++n;
    printf("Se necesita el factorial de %ld, que vale %ld para la precision deseada con x0 = -1.\n", n, n_factorial);
    */

    while ((E/(n_factorial)) > precision) n_factorial *= ++n;
    printf("\nSe necesita el factorial de %ld+1, que vale %ld para la precision deseada con x0.\n", n-1, n_factorial);
    printf("Para comprobarlo, podemos ver que la precision obtenida sera de %le.\n", E/(n_factorial));
    
    
    /*   Voy a escribir un algoritmo que para una x0 y un épsilon de tolerancia, puede calcular el grado correcto para el polinomio de Taylor
    y usarlo para calcular una aproximación. Como los valores de x son cercanos a x0, los describiré con:
    x = x0 + epsilon con -1 <= epsilon <= 1.*/
    
    int pruebas[] = {3, 6, -6, 5};
    for (i = 0; i < 4; i++){
        
        n_factorial = 1;
        n = 1;
        epsilon = ((double) rand() / (double) RAND_MAX);
        temp_epsilon = epsilon;
        x0 = pruebas[i];
        x = x0 + epsilon;
        aprox = 1;
        
        printf("\nCalculemos e^x con el polinomio de Taylor, centrado en x0 = %d, con x = %d + %f, y con una precision de %le\n", x0, x0, epsilon, precision);

        /* Para calcular una n apropiada, necesitamos que se cumpla la inecuación descrita en el word. */

        while ((exp(x0)/(n_factorial))*temp_epsilon > precision) {
            n_factorial *= ++n;
            temp_epsilon *= epsilon;
        }
        
        
        printf("El factorial de %ld+1 vale %ld, lo cual cumple la desigualdad.\n", n-1, n_factorial);
        printf("Se ve que %le es menor que %le.\n", (exp(x0)/(n_factorial))*temp_epsilon, precision);

        /*  Con esto, tenemos el grado que necesitábamos para calcular el polinomio.
            Solo queda hacer la aproximación haciendo uso de la serie de Taylor. */

        
        long int temp_k_factorial = 1;
        temp_epsilon = epsilon;
        for (k = 1; k <= n; k++) {
            temp_k_factorial *= k;
            aprox += pow(epsilon, k)/(temp_k_factorial);
        }
        aprox *= exp(x0);

        printf("Nos da que el valor de la aproximacion es %.16le, el valor real es %.16le.\n", aprox, exp(x));
        printf("El error absoluto cometido es %le y su error relativo es del %le%%.\n", fabs(aprox-exp(x)), fabs(aprox-exp(x))/exp(x));

        printf("\n");

    }
    
    return 0;
}
