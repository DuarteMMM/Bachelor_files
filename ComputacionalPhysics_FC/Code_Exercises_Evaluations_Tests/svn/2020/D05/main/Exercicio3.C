/******************************************************
 *                Física Computacional                *
 *                    Exercício 3                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio>
#include <typeinfo>

int main ()
{
  printf ("\n-=-=-=- Espaço de tipos de variáveis -=-=-=-\n\n");

  printf ("short int:    %lu bytes\n"  , sizeof(short int))   ;
  printf ("int:          %lu bytes\n"  , sizeof(int))         ;
  printf ("long int:     %lu bytes\n"  , sizeof(long int))    ;
  printf ("unsigned int: %lu bytes\n"  , sizeof(unsigned int));
  printf ("float:        %lu bytes\n"  , sizeof(float))       ;
  printf ("double:       %lu bytes\n"  , sizeof(double))      ;
  printf ("long double:  %lu bytes\n\n", sizeof(long double)) ;
  
  return 0;
}
