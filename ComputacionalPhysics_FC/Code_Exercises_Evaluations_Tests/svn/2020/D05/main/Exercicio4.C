/******************************************************
 *                Física Computacional                *
 *                    Exercício 4                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio>
#include <cmath>

int main ()
{
  float  pi_float ;
  double pi_double;
  pi_float  = atan(1)*4;
  pi_double = atan(1)*4;

  // Usando os "%.9g" e "%.17g" (encontrei pdf a explicar que estes dão a precisão "máxima" de float e double, restringindo o número de caracteres)
  
  printf ("\nValor de PI usando atan() com precisão de float:  %.9g",  pi_float) ;
  printf ("\nErro face ao valor verdadeiro: %.9g\n"   ,  (pi_float-M_PI)/M_PI)   ;
  printf ("\nValor de PI usando atan() com precisão de double: %.17g", pi_double);
  printf ("\nErro face ao valor verdadeiro: %.17g\n\n", (pi_double-M_PI)/M_PI)   ;

  return 0;
}
