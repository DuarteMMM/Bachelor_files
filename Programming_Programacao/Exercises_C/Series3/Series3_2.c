/* **************************************************************************
*                                                                           *
*              Série 3 (28/10/2019), exercício 2 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função que calcula o número de ocorrências do primeiro caracter na string

int ocorrencias (char *texto, char a)
{
  int d;                // Comprimento da string
  d = strlen (texto);

  int i;                // Contador
  i = 0;
  
  int total;            // Número de ocorrências
  total = 0;

  // Cálculo do número de ocorrências
  
  while (i <= d)
    {
      if (texto [i] == a)
	total += 1;

      i += 1;
    }

  return total;
}

// Função que retorna a primeira posição do primeiro caracter digitado na string

int posicao (char *texto, char a)
{
  int d;               // Comprimento da string
  d = strlen (texto);
  
  int i;               // Contador
  i = 0;

  int posicao;         // Primeira posição do caracter
  posicao = -1;
  
  while (i <= d)
    {
      if (texto [i] == a)
	{
	  posicao = i;
	  break;
	}

      i += 1;
    }

  return posicao;
}

// Função que substitui, na string, o primeiro caracter digitado pelo segundo

char* substituir (char *texto, char a, char b)
{
  int d;               // Comprimento da string
  d = strlen (texto);
  
  int i;               // Contador
  i = 0;

  while (i <= d)
    {
      if (texto [i] == a)
	texto [i] = b;

      i += 1;
    }

  return texto;
}
	  

int main (int argc, char **argv)
{
  // Declaração de variáveis e atribuição de valores

  int   d;                       // Comprimento da primeira string digitada
  int   x1, x2;                  // Comprimento da segunda e terceira strings digitadas, respetivamente
  int   o;                       // Número de ocorrências do primeiro caracter na string
  int   primeira_posicao;        // Primeira posição do primeiro caracter digitado na string
  char  *texto;                  // String digitada, copiada, para ser argumento da terceira função

  // Teste: verificar se se digitaram 3 elementos, seguidos ao nome do programa
  
  if ((argc != 4))
    {
      printf ("\nERRO: Deve digitar '[string] [caracter] [caracter]'.\n");
      printf ("\n");
      return 1;
    }

  // Testar se o comprimento da segunda e terceira strings digitadas é 1 (terá de ser, porque estes têm de ser caracteres)
  
  x1 = strlen (argv [2]);
  x2 = strlen (argv [3]);

  if ((x1 != 1) || (x2 != 1))
    {
      printf ("\nERRO: Deve digitar '[string] [caracter] [caracter]'.\n");
      printf ("\n");
      return 1;
    }

  printf ("\n *-*-*-*-* Strings *-*-*-*-*\n");

  // Executar a primeira função
  
  o = ocorrencias (argv [1], *argv [2]);

  printf ("\n- O caracter '%c' encontra-se %d vez(es) na string '%s'.\n", *argv [2], o, argv [1]);

  // Executar a segunda função
  
  primeira_posicao = posicao (argv [1], *argv [2]);

  if (primeira_posicao >= 0)
    printf ("\n- O caracter '%c' aparece, pela primeira vez, na %dª posição da string '%s'.\n", *argv [2], (primeira_posicao + 1), argv [1]);

  if (primeira_posicao == -1)
    printf ("\n- (-1)\n");

  // Executar a terceira função

  d = strlen (argv [1]);                                // Comprimento da string original

  texto = (char*) malloc ((d + 1) * sizeof (char));     // Alocar o espaço necessário para copiar a string

  texto = argv [1];                                     // Copiar a string

  texto = substituir (texto, *argv [2], *argv [3]);     // Nova string

  printf ("\n- Substituiu-se, na string, os caracteres '%c' pelo caracter '%c'.", *argv [2], *argv [3]);
  printf ("\n  A string modificada é '%s'.\n", texto);

  // Terminar o programa

  printf ("\n «FIM»\n");
  printf ("\n");

  return 0;
}
