/* **************************************************************************
*                                                                           *
*              Série 1 (14/10/2019), exercício 3 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>

//Definição da função//

void fibonacci (int *f, int i)
{
    f[0] = 0;
    f[1] = 1;
    int x;
    
    for (x=2; x<i; x++)
      {
	f[x] = f[x-1]+f[x-2];
      }
}

int main()
{
  printf ("\n*-*-*-*-* SUCESSÃO DE FIBONACCI *-*-*-*-*\n");
  
  //Declaração de variáveis e abertura do ficheiro//

  int teste, i, x, f[46];
  FILE *f1;
  f1 = fopen ("fibonacci.txt", "wt");

  //Testar a abertura do ficheiro//

  if (f1 == 0)
    {
      printf ("\nERRO: o ficheiro não abriu corretamente!\n");
      return 1;
    }
  
  //Leitura do número de elementos da sequência pedidos//

  printf ("\nEscolha quantos elementos da sucessão de Fibonacci deseja saber (no máximo, 45):\n");
  teste = scanf ("%d", &i);

  //Testar leitura de i//

  if (i>45)
    {
      printf ("\nEscolheu mais do que 45 elementos.\n\n");
      return 2;
    }
  if (teste==0)
    {
      printf ("\nInseriu algo inválido.\n\n");
      return 3;
    }

  //Escrita de valores no ecrã e no ficheiro (seis por linha e alinhados à esquerda)//
  
  if (i<=45)
    {
      fibonacci (f, i);
      printf ("\nA sucessão de Fibonacci, até ao elemento número %d, é:\n\n", i);
      for (x=0; x<i; x++)
        {
	  printf ("%-10d", f[x]);
	  fprintf (f1, "%-10d", f[x]);

	  if ( ( ( (x+1) %6 ) == 0 ) && ( x != 0 ) )
            {
                printf ("\n");
                fprintf (f1, "\n");
            }
	}
    }

  printf ("\n\n");

  //Fechar o ficheiro e terminar o programa//

  fclose (f1);
  return 0;
}
