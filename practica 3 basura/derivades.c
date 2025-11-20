/**
 * Karim Boujana Marcucci.
 */

 /**
  * 
  * double f_1(double x) { return exp(x); }
  * double f_2(double x) { return fabs(x); }
  * double f_3(double x) { return 1/(1+25*x*x); }
  * double f_3(double x) { return pow(1/(1+25*x*x), 2); }
  */

double f_4(double x);
double der (double x0, double h) { return (f_4(x0+h) - f_4(x0))/h; }
double derCen (double x0, double h) { return (f_4(x0+h) - f_4(x0-h))/(2.0*h); }