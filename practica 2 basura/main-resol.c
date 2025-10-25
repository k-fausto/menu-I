/**
 * Karim Boujana Marcucci.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *triangSup (int n , double ** matU , double *b);
int elimGaus (int n , double **a , double *b , double tol);

int main(void) {

   char input_filename[100];
   char output_filename[100];
   FILE *input_file, *output_file;
   int dimension, i, j, k;
   double tol, maximum_norm_A = 0, maximum_norm_diff = 0, maximum_norm_x = 0, temp = 0;

   /* Leemos el camino al archivo. */
   printf("Enter the input filename: ");
   scanf("%99s", input_filename);

   /* Lo intetamos leer. */
   input_file = fopen(input_filename, "r");
   if (input_file == NULL) { printf("Archivo no se puede abrir: %s\n", input_filename); return 1; }

   /* Intetamos leer la dimensión. */
   if (fscanf(input_file, "%d", &dimension) != 1) {
      printf("No se pudo leer la dimensión del sistema.\n");
      fclose(input_file);
      return 1;
   }

   /* Reservamos memoria dinámicamente. */
   double **system = (double **)malloc(dimension * sizeof(double *));
   double *b = (double *) malloc(dimension * sizeof(double));
   for (i = 0; i < dimension; i++) system[i] = (double *)malloc(dimension * sizeof(double));
   

   /* Rellenamos la matriz y el vector b y a la vez calculamos la norma máxima de A. */
   for (i = 0; i < dimension; i++) {

      for (j = 0; j < dimension + 1; j++) {

         if (fscanf(input_file, "%lf", &system[i][j]) != 1) {
            /* Liberamos la memoria antes de acabar el programa si encontramos un error. */
            printf("Error leyendo el sistema.\n");
            for (k = 0; k < dimension; k++) free(system[k]);
            free(system);
            fclose(input_file);
            return 1;
            
         }

         else if (j == dimension) {
            if (fscanf(input_file, "%lf", &b[j]) != 1) {
               /* Liberamos la memoria antes de acabar el programa si encontramos un error. */
               printf("Error leyendo el término independiente.\n");
               for (k = 0; k < dimension; k++) free(system[k]);
               free(system);
               fclose(input_file);
               return 1;
            }

         }

         maximum_norm_A = maximum_norm_A < fabs(system[i][j]) ? fabs(system[i][j]) : maximum_norm_A;

      }
      
   }

   /* Leemos la tolerancia. */
   if (fscanf(input_file, "%lf", &tol) != 1) {

         printf("Error leyendo la tolerancia.\n");
         for (i = 0; i < dimension; i++) free(system[i]);
         free(system);
         fclose(input_file);
         return 1;

      }

   /* Leemos el archivo de salida. */
   if (fscanf(input_file, "%s", output_filename) != 1) {

      printf("Error leyendo el nombre del archivo de salida.\n");
      for (i = 0; i < dimension; i++) free(system[i]);
      free(system);
      fclose(input_file);
      return 1;
      
   }

   /* Resolvemos el sistema. */
   double* solution;
   if (elimGaus(dimension, system, b, tol) == -1) { printf("Sistema irresoluble.\n"); return 1; }
   solution = triangSup(dimension, system, b);

   /* Abrimos el archivo. */
   output_file = fopen(output_filename, "w");
   if (output_file == NULL) { printf("No se pudo crear el archivo: %s\n", output_filename); return 1; }

   /* Calculamos la norma máxima de Ax - b. */
   for (i = 0; i < dimension; i++) {

      for (j = 0; j < dimension; j++) temp += system[i][j] * solution[j];
      temp -= b[i];
      maximum_norm_diff = maximum_norm_diff < fabs(temp) ? fabs(temp) : maximum_norm_diff;

   }

   /* Escribimos la solución y de paso calculamos la norma máxima de x. */
   for (i = 0; i < dimension; i++) {
      maximum_norm_x = maximum_norm_x < fabs(solution[i]) ? fabs(solution[i]) : maximum_norm_x;
      if (i != dimension-1) fprintf(output_file, "%le", solution[i]);
      else fprintf(output_file, "%le\n", solution[i]);
   }

   /* Escribimos cada norma. */
   fprintf(output_file, "Norma máxima de A: %le\n", maximum_norm_A);
   fprintf(output_file, "Norma máxima de Ax-b: %le\n", maximum_norm_diff);
   fprintf(output_file, "Norma máxima de x: %le", maximum_norm_x);

   /* Limpiamos la memoria. */
   for (i = 0; i < dimension; i++) free(system[i]);
   free(system);
   fclose(input_file);

   return 0;
}