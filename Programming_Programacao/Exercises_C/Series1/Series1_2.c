/* **************************************************************************
*                                                                           *
*              Série 1 (14/10/2019), exercício 2 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função bubble_sort//

void bubble_sort (float *r1, int qt)
{
  //Declaração de variáveis//
  
  int t, i1;
  float x1;
  
  while (1)
    {
      t=0;

      //Trocar a ordem dos elementos//
      
      for (i1=0; i1<qt-1; ++i1)
	{
	  if (r1[i1]>r1[i1+1])
	    {
	      x1 = r1[i1];
	      r1[i1] = r1[i1+1];
	      r1[i1+1] = x1;
	      t=1;
	    }
	}

      //Parar a execução da função quando os elementos estão ordenados//
      
      if (t==0)
	break;
    }
}		

int main()
{
  printf("\n*-*-*-*-* Ordenação de valores aleatórios *-*-*-*-*\n");
  
  //Declaração de variáveis e atribuição de valores//
  
  int n, teste, teste1, i, i2;
  float x, max;
  FILE *f1;
  f1 = fopen("valores aleatórios", "wt");
  i=0;
  i2=0;

  //Testar a abertura do ficheiro//

  if (f1==0)
    {
      printf ("\nERRO: O ficheiro não abriu corretamente.\n");
      return 1;
    }

  //Valores a pedir//
  
  printf ("\nQuantos números aleatórios deseja gerar?\n");
  teste = scanf ("%d", &n);
  printf ("\nQual o valor máximo?\n");
  teste1 = scanf ("%f", &max);

  //Testar a leitura de valores//

  if ((teste==0) || (n<1) || (teste1==0))
    {
      printf ("\nDigitou 1 ou 2 valor(es) inválido(s).\n\n");
      return 2;
    }

  //Atribuição de valores aleatórios ao vetor//
  
  float a[n];
  srand (time (NULL));
  printf ("\nEis os valores aleatórios:\n\n");
  while (i < n)
    {
      x = ((((float) rand()) /((float) RAND_MAX) ) * max);
      a[i] = x;
      printf ("%f\n", a[i]);
      i=i+1;
    }

  //Execução da função bubble_sort e escrita dos valores ordenados//

  bubble_sort (a, n);
  printf ("\nOs valores, por ordem crescente são os seguintes: \n\n");
  while (i2<n)
    {
      printf ("Valor n.%d: %f\n", i2+1, a[i2]);
      fprintf (f1, "%f\n", a[i2]);
      i2 = i2+1;
    }

  printf ("\nFIM\n\n");

  fclose (f1);
  
  return 0;
  
}
	   
	    
		 
      

