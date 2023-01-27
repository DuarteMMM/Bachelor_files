/* ***************************************************************************
 *                                                                           *
 *              Série 8 (02/12/2019), exercício 1 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define incremento 1e-5

// Main

int main (int argc, char **argv)
{
  printf  ("\n*-*-*-*-* Equações diferenciais do tipo dx/dt = -ax *-*-*-*-*\n\n");
  
  // Declaração das Variáveis
  
  double  a  = 0 ; // Constante de elasticidade
  double  x0 = 0 ; // Valor inicial
  double  ti = 0 ; // Tempo inicial
  double  tf = 0 ; // Tempo final
  double  t  = 0 ; // Para cálculo dos valores
  double  x  = 0 ; // Para cálculo dos valores
  
  int   nr_ciclos = 1   ; // Número de ciclos no cálculo de valores
  FILE  *Eq_diferencial ; // Ficheiro

  // Input

  if (argc == 5 && sscanf (argv[1], "%lf", &a) == 1 && sscanf (argv[2], "%lf", &x0) == 1 && sscanf (argv[3], "%lf", &ti) == 1 && sscanf (argv[4], "%lf", &tf) == 1 && ti < tf)
    printf ("=> Input detetado na linha de comandos:\n - a  = %6.2lf\n - x0 = %6.2lf\n - ti = %6.2lf\n - tf = %6.2lf\n", a, x0, ti, tf);

  else
    {
      printf ("=> Não foram dados argumentos válidos na linha de comandos.\n=> Poderá agora dar os argumentos necessários ao funcionamento do programa, sendo que:\n - Todos os argumentos dados deverão ser números reais;\n - Um argumento inválido irá terminar o programa;\n - tf > ti;\n - Também poderá dar os argumentos quando evoca o programa ('./[nome do programa] a x0 ti tf').\n\n");

      printf ("\n=> Qual o valor de a?\n   ");
      if (scanf ("%lf", &a) != 1)
	{
	  printf ("=> ERRO: Valor inválido\n\n");
	  return 1;
	}
	  
      printf ("\n=> Qual o valor inicial de x (x0)?\n   ");
      if (scanf ("%lf", &x0) != 1)
	{
	  printf ("=> ERRO: Valor inválido\n\n");
	  return 2;
	}

      printf ("\n=> Qual o valor inicial de t (ti)?\n   ");
      if ((scanf ("%lf", &ti) != 1) || (ti < 0))
	{
	  printf ("=> ERRO: Valor inválido\n\n");
	  return 3;
	}

      printf ("\n=> Qual o valor final de t (tf)?\n   ");
      if (scanf ("%lf", &tf) != 1 || ti >= tf)
	{
	  printf ("=> ERRO: Valor inválido\n\n");
	  return 4;
	}

      printf ("\n=> Input detetado:\n - a  = %6.2lf\n - x0 = %6.2lf\n - ti = %6.2lf\n - tf = %6.2lf\n", a, x0, ti, tf);
    }


  // Abertura do Ficheiro
  
  Eq_diferencial = fopen ("Eq_diferencial.txt", "wt");
  if (Eq_diferencial == NULL)
    {
      printf ("\n\n=> ERRO: O ficheiro não abriu corretamente.\n\n");
      return 5;
    }
      

  // Cálculo da função

  printf ("\nValores da função:\n\n");
  
  x = x0;

  fprintf (Eq_diferencial, " %lf %lf\n", ti, x);
  
  for (t = ti; t <= tf; t = t + incremento)
    {
      x = x - a*x*incremento;

      if ((nr_ciclos % 1000) == 0)
	printf ("x (%6.2lf) = %lf\n", t, x);  // Deste modo, não se escrevem demasiado valores no terminal
      
      fprintf (Eq_diferencial, " %lf %lf\n", t, x);  // No ficheiro, porém, são escritos todos os valores

      nr_ciclos += 1;
    }
      
  // Finalizar o programa

  fclose (Eq_diferencial);
  printf ("\n-FIM-\n\n");
  return 0;
}
