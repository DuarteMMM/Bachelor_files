/* ***************************************************************************
 *                                                                           *
 *              Série 7 (25/11/2019), exercício 4 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função a executar no caso de digitações incorretas no terminal

void help ()
{
  printf ("\n *-*-*-*-* Contagens do ficheiro *-*-*-*-*\n");
  printf ("\nERRO: Digitou algo inválido. Deve escrever:\n");
  printf ("\n ./[nome do programa] [nome do ficheiro]\n");
  printf ("\nNota: o ficheiro deve ser criado previamente por si.\n");

  printf ("\n");

  exit (1);
}

int main (int argc, char** argv)
{
  // Declaração de variáveis
  
  FILE  *f             ;   // Ficheiro de leitura
  int   v [256]        ;   // Vetor de ASCII
  int   i              ;   // Contador
  int   x              ;   // Valor ASCII de caracter
  int   total = 0      ;   // Total de caracteres
  int   vogais = 0     ;   // Total de vogais
  int   consoantes = 0 ;   // Contador de consoantes

  // Teste da quantidade de valores digitados no terminal

  if (argc != 2) 
    help ();
    
  // Abertura e teste de abertura do ficheiro

  f = fopen (argv [1], "rt");

  if (f == NULL)
    {
      printf("\nERRO: O ficheiro '%s' não foi encontrado ou não abriu corretamente.\n", argv [1]);
      printf ("\n");
      return 1;
    }

  printf ("\n *-*-*-*-* Contagens do ficheiro *-*-*-*-*\n");

  // Preenchimento do vetor de ASCII com zeros
 
  for (i = 0; i <= 255; i++)
    v [i] = 0;

  for (i = 0 ; x != EOF; i++)
    {
      x = fgetc (f); // Lê o caracter como inteiro

      if (x == EOF)
	break;
      
      v [x] += 1;  // Se se vir esse caracter no ficheiro, à posição do vetor para esse valor soma-se 1 (porque há mais 1 desse caracter) 
    }

  // Alínea a): número total de caracteres
 
  for (i = 0; i <= 255; i++)
    {
      if (v [i] != 0)
	total = total + v [i];   // Soma-se ao total o número de vezes que há o caracter x/i, inteiro de código ASCII
    }
 
  printf ("\nO texto tem um total de %d caracteres.\n\n", total);
 
  // Alínea b): cada caracter e número de ocorrências (se houverem ocorrências)

  for (i = 0; i < 33; i++)
    {
      if (v [i] != 0)
	{
	  if (v [i] == 1)
	    printf ("O caracter ASCII %d surge %d vez.\n", i, v [i]);  // Para caracteres estranhos que aparecem 1 vez

	  if (v [i] > 1)
	    printf ("O caracter ASCII %d surge %d vezes.\n", i, v [i]);  // Para caracteres estranhos que aparecem várias vezes
	}
    }

  for (i = 33; i <= 126; i++)
    {
      if (v [i] != 0)
	{
	  if (v [i] == 1)
	    printf("O caracter '%c' surge %d vez.\n", i, v [i]);

	  if (v [i] > 1)
	    printf("O caracter '%c' surge %d vezes.\n", i, v [i]);
	}
    }

    for (i = 127; i <= 255; i++)
    {
      if (v [i] != 0)
	{
	  if (v [i] == 1)
	    printf ("O caracter ASCII %d surge %d vez.\n", i, v [i]);  // Para caracteres estranhos que aparecem 1 vez

	  if (v [i] > 1)
	    printf ("O caracter ASCII %d surge %d vezes.\n", i, v [i]);  // Para caracteres estranhos que aparecem várias vezes
	}
    }

  // Alínea c): número de vogais no texto

  vogais = v [65] + v [69] + v [73] + v [79] + v [85] + v [97] + v [101] + v [105] + v [111] + v [117]; // Somar número de ocorrências de 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o' e 'u', nesta ordem
  
  printf("\nO texto tem um total de %d vogais.\n", vogais);

  // Alínea d): número de consoantes
  
  for (i = 65; i <= 90; i++)
    consoantes = consoantes + v [i]; // Somar ocorrências de todas as letras maiúsculas

  for (i = 97; i <= 122; i++)
    consoantes = consoantes + v [i]; // Somar ocorrências de todas as letras minúsculas
 
  consoantes = consoantes - vogais; // Remover ao total de letras o total de vogais
  
  printf("\nO texto tem um total de %d consoantes.\n", consoantes);

  // Finalizar o programa

  fclose (f);
  printf ("\n-FIM-\n\n");
  return 0;
}
