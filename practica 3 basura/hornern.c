/**
 * Karim Boujana Marcucci.
 */

double hornerNew (int n , double *b , double *x , double z) {
    
    double result = b[n];
    int i = 0;

    for (i = n-1; i >= 0; i--) {
        result *= z-x[i];
        result += b[i];
    } 

    return result;

}