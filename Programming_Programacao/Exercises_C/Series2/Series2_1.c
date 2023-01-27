/* **************************************************************************
*                                                                           *
*              Série 2 (21/10/2019), exercício 1 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort (double *r1, int qt)
{
  //Declaração de variáveis//
  
  int t, i1;
  double x1;
  
  while (1)
    {
      t = 0;

      //Trocar a ordem dos elementos//
      
      for (i1 = 0; i1 < qt-1; ++i1)
	{
	  if (r1 [i1] > r1 [i1+1])
	    {
	      x1 = r1 [i1];
	      r1 [i1] = r1 [i1+1];
	      r1 [i1+1] = x1;
	      t = 1;
	    }
	}

      //Parar a execução da função quando os elementos estão ordenados//
      
      if (t == 0)
	break;
    }
}		

int main (int argc, char **argv)
{  
  //Declaração de variáveis e atribuição de valores//
  
  int n;                                  //Número de valores a gerar//
  float max;                              //Valor máximo para os números gerados//
  int teste, teste1, teste2, teste3;      //Testes de leitura de valores//
  int i, i2, r, ciclos;                   //Usados na execução de ciclos//
  double x;                               //Sucessivos números aleatórios gerados//
  double *p;                              //Vetor dos números aleatórios//
  FILE *f1;                               //Ficheiro de escrita//

  r = 0;
  ciclos = 0;

  //Testar a leitura de valores no terminal//

  if (argc == 3)
    {
      teste = sscanf (argv [1], "%f", &max);    
      teste1 = sscanf (argv [2], "%d", &n);
      
      if ((teste == 0) || (teste1 == 0) || (max < 0) || (n < 1) || ((n % 1) != 0))
	{
	  /*  A condição (n%1)!=0 foi aqui colocada porque, embora o programa corresse quando se digitava, para n, 
	      um número real positivo, mais à frente, o programa era executado deficientemente;
	      Colocando esta condição, impõe-se, portanto, que n seja natural.                                    */ 
	  
	  printf ("\nDigitou algo inválido. Deve escrever um número real não negativo seguido de um número natural.\n");
	  printf ("\nFIM\n");
	  printf ("\n");
	  return 1;
	}

      else
	{
	  printf ("\n*-*-*-*-* Ordenação de valores aleatórios *-*-*-*-*\n");
	  printf ("\nValor máximo: %f\nNúmero de valores: %d\n", max, n);
	}
    }
  
  while (r == 0)
    {
      i = 0;
      i2 = 0;

      //Pedir os valores, no caso de o utilizador não dar argumentos no teminal ou no caso de não se tratar do primeiro ciclo//

      if ((ciclos > 0) || (argc != 3))
	{
	    
	  if (ciclos == 0)
	    {
	      printf ("\nNão digitou dois valores no terminal.\n");
	      printf("\n*-*-*-*-* Ordenação de valores aleatórios *-*-*-*-*\n");
	    }
	  
	  printf ("\nDigite o valor máximo (do intervalo [O, MÁXIMO]):\n");
	  teste2 = scanf ("%f", &max);
	  
	  //Testar a leitura do primeiro valor//
	  
	  if  ((teste2 == 0) || (max < 0))
	    {
	      printf ("\nDigitou algo inválido. Deve escrever um número real não negativo.\n");
	      printf ("\nFIM\n");
	      printf ("\n");

	      //Fechar o ficheiro e libertar a memória, se tal for necessário//

	      if (ciclos > 0)
		{
		  fprintf (f1, "FIM");
		  fclose (f1);
		  free (p);
		}

	      return 2;
	    }
      
	  printf ("\nDigite o número de valores:\n");
	  teste3 = scanf ("%d", &n);

	  //Testar a leitura do segundo valor//

	  if ((teste3 == 0) || (n < 1) || ((n % 1) != 0))
	    {
	      printf ("\nDigitou algo inválido. Deve digitar um número natural.\n");
	      printf ("\nFIM\n");
	      printf ("\n");

	      //Fechar o ficheiro e libertar a memória, se tal for necessário//

	      if (ciclos > 0)
		{
		  fprintf (f1, "FIM");
		  free (p);
		  fclose (f1);
		}

	      return 3;
	    }
	}

      //Abertura do ficheiro e teste da abertura//

      if (ciclos == 0)
	{
	  f1 = fopen ("Valores aleatórios", "wt");

	  if (f1 == NULL)
	    {
	      printf ("\nERRO: O ficheiro não abriu corretamente.\n");
	      printf ("\nFIM\\n");
	      printf ("\n");
	      return 4;
	    }
	  
	  fprintf (f1, "*-*-*-*-* Números aleatórios ordenados *-*-*-*-*\n\n");
	}

      //Definir ou redefinir o tamanho do vetor//
      
      if (ciclos == 0)
	p = (double *) malloc (n * sizeof (double));
      if (ciclos > 0)
	p = (double *) realloc (p, n * sizeof (double));

      //Atribuição de valores aleatórios ao vetor e escrita desses valores//
      
      printf ("\n«CICLO N. %d»\n", ciclos + 1);
      srand (time (NULL));
      printf ("\nEis os valores aleatórios:\n\n");

      while (i < n)
	{
	  x = ((( (double) rand() ) /( (double) RAND_MAX ) ) * max);
	  p [i] = x;
	  printf ("%lf\n", p [i]);
	  i = i+1;
	}

      //Execução da função bubble_sort e escrita dos valores ordenados//

      bubble_sort (p, n);
      
      fprintf (f1, "«Ciclo n.%d»\n", ciclos + 1);
      fprintf (f1, "Valor máximo: %f\nNúmero de valores: %d\n", max, n);
      printf ("\nOs valores, por ordem crescente, são os seguintes: \n\n");
      
      while (i2<n)
	{
	  printf ("Valor n.%d: %lf\n", i2+1, p [i2]);
	  fprintf (f1, "Valor n.%d: %lf\n", i2 + 1, p [i2]);
	  i2 = i2+1;
	}

      fprintf (f1, "\n");

      ciclos += 1;

      //Perguntar ao utilizador se deseja continuar//
      
      printf ("\nDeseja continuar? [0]Sim ou [1]Não ?\n");
      teste2 = scanf ("%d", &r);
      
      if (r==1)
	break;

      //Testar a leitura//
      
      if ((teste2 != 1) || ((r!=0) && (r!=1)))
	{
	  printf ("\nDigitou algo inválido.\n\n");
	  printf ("\nFIM\n");
	  printf ("\n");
	  fprintf (f1, "FIM");
	  fclose (f1);
	  free (p);
	  return 5;
	}
    }

  //Libertar a memória do vetor, fechar o ficheiro e terminar o programa//

  printf ("\nFIM\n");
  printf ("\n");
  fprintf (f1, "FIM");
  fclose (f1);
  free (p);
  return 0;
}
  
