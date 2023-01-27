/* ***************************************************************************
 *                                                                           *
 *              Série 8 (02/12/2019), exercício 2 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void help ()
{
  printf ("\nERRO: Deve escrever no terminal: './[nome do programa] N'.\n\n N é o número de linhas do triângulo, logo é um número natural.\n\n");
  exit (1);
}

int main (int argc, char **argv)
{
  int   teste   ;      // Para teste de leitura de n
  char  *ptr    ;      // Para teste de leitura de n
  int   n       ;      // Número de linhas
  int   i = 0   ;      // Contador
  int   j = 1   ;      // Contador
  int   k = 0   ;      // Contador

  // Testes de leituras do terminal
  
  if (argc != 2)
    help ();

  n = strtol (argv [1], &ptr, 10);
  
  if (((*ptr) != 0) || (argv [1] <= 0))
    help ();
    
  // Leitura do valor de n do terminal
    
  sscanf (argv [1], "%d", &n);

  // Desenho do triângulo

  while (i < n)
    {
      while (k < (n - (i + 1) ) )
	{
	  printf (" ");
	  k += 1;
	}

      k = 0;

      while (j <= (i + 1) )
	{
	  printf ("*");
	  printf (" ");
	  j += 1;
	}

      printf ("\n");

      j = 1;

      i += 1;
    }

  return 0;
}
