/******************************************************
 *                Física Computacional                *
 *             Exercício 14, alínea a (e d)           *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include "./Exercicio14a_fintv.h"
#include "./Exercicio14a_fdoublev.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {

  int *a = fintv (100, a);
  double *b = fdoublev (100, b);

  free (a);
  free (b);
  
  return 0;
}
