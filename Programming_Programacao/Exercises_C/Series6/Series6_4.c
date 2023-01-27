/* ***************************************************************************
 *                                                                           *
 *              Série 6 (18/11/2019), exercício 4 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função executada no caso de incorreta digitação por parte do utilizador

void help()
{
  printf ("\nERRO: Deve escrever uma das seguintes opções:\n");
  
  printf ("\n(1) ./[nome do programa] Soma [nome do ficheiro1] [nome do ficheiro2]\n");
  printf ("\n Neste caso, será calculada a matriz-soma das matrizes que se encontram nos ficheiros 1 e 2, criados por si.\n");
  
  printf ("\n(2) ./[nome do programa] Subtração [nome do ficheiro1] [nome do ficheiro2]\n");
  printf ("\n Neste caso, será calculada a matriz-subtração das matrizes que se encontram nos ficheiros 1 e 2, criados por si.\n");
  
  printf ("\n(3) ./[nome do programa] Produto [nome do ficheiro1] [nome do ficheiro2]\n");
  printf ("\n Neste caso, será calculada a matriz-produto entre, respetivamente, as matrizes dos ficheiros 1 e 2, criados por si.\n");

  printf ("\nNota:  A primeira linha do seu ficheiro deverá conter o número de linhas e colunas da matriz, respetivamente.\n");
  printf ("       Cada número deve estar separado do outro por um espaço em branco.\n");
  printf ("       Se colocar um caracter não númerico na matriz, é atribuído o valor zero a qualquer entrada.\n");
  
  printf ("\n");
  exit (1);
}

// Função que dá matriz e dimensões

double **matriz (FILE *f, double *linhas, double *colunas)
{
  int    teste    ;  // Teste para ler colunas e linhas
  double **matriz ;  // Matriz

  // Testar leitura do número de linhas e número de colunas do ficheiro
  
  teste = fscanf (f, "%lf %lf", linhas, colunas);

  if (teste != 2)
    help ();

  int i = 0  ; // Contador para alocar espaço para linhas

  matriz = (double**) malloc ( ((int)*linhas) * sizeof (double) );   // Alocar espaço para o vetor com as linhas

  while (i < *linhas)
    {
      matriz [i] = (double*) malloc ( ((int)*colunas) * sizeof (double) );  // Alocar espaço para cada linha
      i += 1;
    }
  
  i = 0; // Contador para linhas

  int j = 0;  // Contador para colunas

  // Ler as entradas da matriz e apresentá-las

  while (i < *linhas)
    {
      j = 0;

      // Para a linha i, ler as colunas
      while (j < *colunas)
	{
	  fscanf (f, "%lf", &matriz [i][j]);
	  j += 1;
	}
      
      i += 1; // Avançar de linha
    }

  return matriz;
}

// Função que faz print, no ecrã, das matrizes

void print_ecra (double **matriz, double linhas, double colunas)
{
  int i = 0 ;   // Contador para linhas
  int j = 0 ;   // Contador para colunas

  printf ("\nNúmero de linhas:  %.0lf\nNúmero de colunas: %.0lf\n", linhas, colunas);
  
  while (i < linhas)
    {
      printf ("\n");
      j = 0;
      
      while (j < colunas)
	{
	  printf ("%15lf   ", matriz [i][j]);
	  j += 1;
	}
      
      printf ("\n");
      i += 1;
    }

  printf ("\n");
}

// Função para a matriz-soma

void adicao (double **matriz1, double **matriz2, double linhas, double colunas, double **adicao)
{
  int i = 0, j = 0;  // Contadores
  
  while (i < linhas)
    {
      
      // Acionar elementos da linha i da matriz aos elementos da outra matriz, coluna a coluna
      
      while (j < colunas)
	{
	  adicao [i][j] = matriz1 [i][j] + matriz2 [i][j];
	  j += 1;
	}
      
      j = 0;
      i += 1; // Avançar de linha
    }
}

// Função para a matriz-subtração

void subtracao (double **matriz1, double **matriz2, double linhas, double colunas, double **subtracao)
{
  int i = 0, j = 0;  // Contadores

  // As operações são análogas às da soma
  
  while (i < linhas)
    {
      while (j < colunas)
	{
	  subtracao [i][j] = matriz1 [i][j] - matriz2 [i][j];
	  j += 1;
	}
      j = 0;
      i += 1;
    }
}

// Função para preencher a matriz-produto

void produto (double **matriz1, double **matriz2, double linhas1, double colunas1, double linhas2, double colunas2, double **produto)
{
  int i , j , k    ;  // Contadores
  double somatorio ;  // Cada elemento da matriz-produto

  for (i = 0; i < linhas1; i++)
    {
      for (j = 0; j < colunas2; j++)
	{
	  for (k = 0; k < linhas2; k++)
	    {
	      somatorio = somatorio + matriz1 [i][k] * matriz2 [k][j];  // Calcular o elemento [i][j] da matriz-produto
	    }

	  produto [i][j] = somatorio;
	  somatorio = 0;   // Colocar a zero para um novo ciclo
	}
    }
}

// Main

int main (int argc, char **argv)
{
  FILE   *f1, *f2                               ;  // Ficheiros com as matrizes
  double **matriz1, **matriz2                   ;  // Matrizes
  double linhas1, colunas1, linhas2, colunas2   ;  // Número de linhas e colunas das matrizes

  // Testar se se digitaram 4 coisas no terminal
  
  if (argc != 4)
    help ();

  // Abertura dos ficheiros e respetivos testes

  f1 = fopen (argv [2], "rt");
  f2 = fopen (argv [3], "rt");

  if (f1 == NULL)
    {
      printf ("\nERRO: O ficheiro 1 não abriu corretamente.\n");
      printf ("\n");
      return 1;
    }

  if (f2 == NULL)
    {
      printf ("\nERRO: O ficheiro 2 não abriu corretamente.\n");
      printf ("\n");
      fclose (f1);
      return 2;
    }

  printf ("\n *-*-*-*-* Operações sobre matrizes *-*-*-*-*\n");

  // Leitura das matrizes dos ficheiros

  matriz1 = matriz (f1, &linhas1, &colunas1);

  matriz2 = matriz (f2, &linhas2, &colunas2);

  // Escrever as matrizes no ecrã
  
  printf ("\nPRIMEIRA MATRIZ\n");

  print_ecra (matriz1, linhas1, colunas1);
  
  printf ("\nSEGUNDA MATRIZ\n");

  print_ecra (matriz2, linhas2, colunas2);

  double **matriz_resultado; // Matriz para o resultado

  // Verificar se se digitou um texto válido para a operação
  
  if (((strcmp (argv [1], "Soma")) != 0) && ((strcmp (argv [1], "Subtração")) != 0) && ((strcmp (argv [1], "Produto")) != 0))
    {
      help ();
      fclose (f1);
      fclose (f2);
    }

  // Se se pediu soma ou subtração, tem de haver igual número de linhas e de colunas

  if ((((strcmp (argv [1], "Soma")) == 0) || ((strcmp (argv [1], "Subtração")) == 0)) && ((linhas1 != linhas2) || (colunas1 != colunas2)))
    {
      printf ("\nOPERAÇÃO INVÁLIDA: Só é possível somar ou subtrair matrizes com o mesmo número de linhas e com o mesmo número de colunas.\n");
      printf ("\n");
      fclose (f1);
      fclose (f2);
      return 3;
    }

  // Se se pediu soma ou subtração, o número de colunas da primeira matriz é igual ao número de linhas da segunda

  if (((strcmp (argv [1], "Produto")) == 0) && (colunas1 != linhas2))
    {
      printf ("\nOPERAÇÃO INVÁLIDA: Só é possível calcular o produto quando o número de colunas da primeira matriz é igual ao número de linhas da segunda matriz.\n");
      printf ("\n");
      fclose (f1);
      fclose (f2);
      return 4;
    }

  int i = 0;  // Contador para alocar espaços

  // Obter a matriz-soma

  if (((strcmp (argv [1], "Soma")) == 0) && (linhas1 == linhas2) && (colunas1 == colunas2))
    {
      matriz_resultado = (double**) malloc ( ((int)linhas1) * sizeof (double) );   // Alocar espaço para o vetor com as linhas

      while (i < linhas1)
	{
	  matriz_resultado [i] = (double*) malloc ( ((int)colunas1) * sizeof (double) );  // Alocar espaço para colunas
	  i += 1;  // Mudar de linha
	}

      adicao (matriz1, matriz2, linhas1, colunas1, matriz_resultado);  // Calcular a matriz

      printf ("\nMatriz resultante da adição:\n");

      print_ecra (matriz_resultado, linhas1, colunas1);   // Apresentar a matriz
    }

  // Obter a matriz-subtração (comandos idênticos aos da soma)

  if (((strcmp (argv [1], "Subtração")) == 0) && (linhas1 == linhas2) && (colunas1 == colunas2))
    {
      matriz_resultado = (double**) malloc ( ((int)linhas1) * sizeof (double) );

      while (i < linhas1)
	{
	  matriz_resultado [i] = (double*) malloc ( ((int)colunas1) * sizeof (double) );
	  i += 1;
	}

      subtracao (matriz1, matriz2, linhas1, colunas1, matriz_resultado);

      printf ("\nMatriz resultante da subtração:\n");

      print_ecra (matriz_resultado, linhas1, colunas1);
    }

  // Obter a matriz-produto (comandos idênticos aos da soma)
  
  if (((strcmp (argv [1], "Produto")) == 0) && (colunas1 == linhas2))
    {
      matriz_resultado = (double**) malloc ( ((int)linhas1) * sizeof (double) );

      while (i < linhas1)
	{
	  matriz_resultado [i] = (double*) malloc ( ((int)colunas2) * sizeof (double) );
	  i += 1;
	}

      produto (matriz1, matriz2, linhas1, colunas1, linhas2, colunas2,  matriz_resultado);

      printf ("\nMatriz resultante do produto:\n");

      print_ecra (matriz_resultado, linhas1, colunas2);
    }

  // Finalizar o programa

  printf ("\n -FIM-\n");
  printf ("\n");

  fclose (f1);
  fclose (f2);

  return 0;
}
