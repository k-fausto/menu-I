/**
 * Karim Boujana Marcucci.
 */

void dif_div(int n, double *x, double *f) {
    int i, j;
    for (j = 1; j <= n; j++) {
        for (i = n; i >= j; i--) {
            f[i] = (f[i] - f[i-1]) / (x[i] - x[i-j]);
        }
    }
}