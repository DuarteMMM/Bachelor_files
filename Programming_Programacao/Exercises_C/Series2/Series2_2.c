/* **************************************************************************
*                                                                           *
*              Série 2 (21/10/2019), exercício 2 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <math.h>

// Função da conversão do valor do ângulo para o intervalo [0, 2*pi[ radianos //

double conv (double x)
{
  x = fmod (x, 2*M_PI);
  
  if (x < 0)
    x = -x;
  
  return x;
}

// Função que calcula um fatorial (por definição, de um número natural ou nulo) - resultado em double //

double fatorial (unsigned int n)
{
  double a1, a2;
  a1 = (double) n;
  a2 = 1.;
  
  while (a1 > 1.)
    {
      a2 = a2 * a1;
      --a1;
    }
  
  return a2;
}

// Função que calcula o valor do cosseno do ângulo pedido através da série de Taylor //

double cos1 (double x1)
{
  unsigned int i;
  double f, p, x2, cos2;
    
  i = 0;
  cos2 = 0.;
  x2 = conv (x1);

  while (fabs (cos2 - cos (x2)) >= 1.E-10)
    {
      f = fatorial (2*i);
      p = (pow (-1, i)) * ((pow (x2, 2*i)) / f);
      cos2 = cos2 + p;
      i++;
    }
  
  return cos2;
}

int main()
{
  //Declaração de variáveis//

  int teste;     // Teste da leitura do ângulo //
  double x, x1;  // Ângulo e seu cosseno, respetivamentente //

  printf ("\n*-*-*-*-* Cálculo do cosseno com erro inferior a 10⁻¹⁰ *-*-*-*-*\n");
    
  // Leitura do ângulo e teste da leitura //
    
  printf ("\nInsira o valor do ângulo, em radianos, cujo cosseno deseja calcular:   ");
  
  teste = scanf ("%lf", &x);
  
  if (teste != 1)
    {
      printf ("\nDigitou algo inválido. Deve digitar um número.\n");
      printf ("\nFIM\n");
      printf ("\n");
      return 1;
    }
  
  // Cálculo do cosseno do ângulo através da função cos1, definida anteriormente //

  x1 = cos1 (x);
    
  printf ("\nValor aproximado do cosseno pelo desenvolvimento da série de Taylor:   %.11lf\n", x1);
  
  printf ("\nValor aproximado do cosseno pela função 'cos' da biblioteca de C:      %.11lf\n", cos (x));

  // Terminar o programa //
  
  printf ("\n-FIM-\n");
  printf ("\n");
  return 0;
}
