#include <math.h>
#include <stdio.h>

int main(void) {
    float fabsf(float);
    int i, n=10;
    double xi_directe, double_xi_rec, double_error_abs, double_error_rel, x0 = 2.0, x1 = 5.0, un_tercio = 1.0/3.0, tres = 3.0, 
            double_xi_rec_menos_dos, double_xi_rec_menos_uno;
    float float_xi_rec, float_error_abs, float_error_rel, float_xi_rec_menos_uno, float_xi_rec_menos_dos;

    /*
    printf("Introduce una n: ");
    scanf("%d", &n); 
    printf("Introduce una x0: ");
    scanf("%lf", &x0); 
    printf("Introduce una x1: ");
    scanf("%lf", &x1); 
    */

    float_xi_rec_menos_dos = (float) x0;
    float_xi_rec_menos_uno = (float) x1;

    double_xi_rec_menos_dos = x0;
    double_xi_rec_menos_uno = x1;

    printf("xi directe \t\t xi float rec\t\terror abs\t\terror rel\t\txi double rec\t\terror abs\t\terror rel\t\t\n");

    for (i = 0; i < n; i++) {

        /**
         * Cálculo directo con double.
         */
        un_tercio *= 1.0/3.0;
        tres *= 3;
        xi_directe = (3.0/8.0) * (3.0 * x0 - x1) * un_tercio + (1.0/8.0) * (3.0 * x1 - x0) * tres;

        /**
         * Cálculo de la recurrencia con float.
         */
        float_xi_rec = (10.0/3.0) * float_xi_rec_menos_uno - float_xi_rec_menos_dos;

        float_xi_rec_menos_dos = float_xi_rec_menos_uno;
        float_xi_rec_menos_uno = float_xi_rec;

        float_error_abs = fabsf(float_xi_rec - xi_directe);
        float_error_rel = float_error_abs/xi_directe;
        
        /**
         * Cálculo de la recurrencia con double.
         */
        double_xi_rec = (10.0/3.0) * double_xi_rec_menos_uno - double_xi_rec_menos_dos;
        
        double_xi_rec_menos_dos = double_xi_rec_menos_uno;
        double_xi_rec_menos_uno = double_xi_rec;

        double_error_abs = fabs(double_xi_rec - xi_directe);
        double_error_rel = double_error_abs/xi_directe;

        printf("%.10le \t%.10le\t%.10le\t%.10le%%\t%.10le\t%.10le\t%.10le%%\t\n", 
            xi_directe, float_xi_rec, float_error_abs, float_error_rel, double_xi_rec, double_error_abs, double_error_rel);


    }

    return 0;
}