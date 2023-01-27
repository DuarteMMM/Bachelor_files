/******************************************************
 *                Física Computacional                *
 *                    Exercício 2                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio>
#include <cmath>

double funcao (double x)
{
  double valor_seno;
  valor_seno = sin(x)*sin(x);
  return valor_seno;
}

int main ()
{
  printf ("\n-=-=-=-=-=- z(x)=x+f(x) -=-=-=-=-=-\n\n");
  
  double x, z;
  int teste_x;

  printf ("Digite o valor de x (em radianos): ");

  teste_x = scanf ("%lf", &x);
  if (teste_x != 1)
    {
      printf ("\n\nDigitou algo inválido.\n\n");
      return 1;
    }

  z = x+funcao(x);

  printf ("\n\nz(x)=%lf\n\n", z);
  return 0;
}
    
  
