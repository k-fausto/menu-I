/**
 * Karim Boujana Marcucci.
 */

#include <stdlib.h>
#include <math.h> 

void dif_div (int n , double *x , double *f ) {

    int i, j;
    
    for (i = 0; i < n; i++) {
        for (j = n - 1; j > i; j--) {
            f[j] = (f[j] - f[j - 1]) / (x[j] - x[j - i - 1]);
        }
    }

}