/******************************************************
 *                Física Computacional                *
 *                    Exercício 10                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream> // cout
#include <cstdio> //printf
#include <cmath> // cos
#include <cstdlib> //rand()
#include <ctime> // srand

int main () {
  float x [1000], y, x_medio=0., desvio_padrao=0.;
  int i = 0;

  printf ("\n-=-=-=- 1000 números aleatórios entre 5 e 55 -=-=-=-\n");
  
  srand (time (NULL));

  printf ("\nValores de x     Valores de y\n");

  while (i<1000)
    {
      x[i] = ((float) rand()) / ((float) RAND_MAX)*50 + 5;
      x_medio += x[i];
      y = x[i] / (x[i] - 10);
      printf ("\n %f         %f", x[i], y);
      i++;
    }

  i=0;
  
  x_medio=x_medio/1000;

  while (i<1000)
    {
      desvio_padrao += (x[0]-x_medio)*(x[0]-x_medio);
      i++;
    }

  desvio_padrao = sqrt (desvio_padrao/1000);

  printf ("\n\n-O valor médio de x é %f.", x_medio);
  printf ("\n-O desvio padrão é %f.", desvio_padrao);
  
  printf ("\n\n -FIM-\n\n");
  return 0;
}
