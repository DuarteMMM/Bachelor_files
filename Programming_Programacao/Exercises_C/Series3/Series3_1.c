/* **************************************************************************
 *                                                                           *
 *              Série 3 (28/10/2019), exercício 1 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// Função que calcula o máximo divisor comum

long long int mdc (long long int a, long long int b)
{
  long long int c, d, e;

  // Fazer com que "a" seja o maior valor digitado
  
  if (b > a)
    {
      e = a;   // Guardar o menor valor
      a = b;   // Atribuir a "a" o maior valor
      b = e;   // Atribuir a "b" o menor valor
    }

  // Ciclo de cálculo de resto da divisão
  
  while (1)
    {
      c = a % b;

      if (c == 0)
	break;
      
      d = b;   // Guardar o valor de "b"
      a = d;   // Atribuir a "a" o valor de "b"
      b = c;   // Atribuir a "b" o valor de "c"
    }
  
  return b;
}

// Função que calcula o mínimo múltiplo comum

long long int mmc (long long int a, long long int b)
{
  long long int y, z;
  z = mdc (a, b);    // Máximo divisor comu
  y = (a * b) / z;   // Mínimo múltiplo comum
  
  return y;
}
  
int main (int argc, char **argv)
{

  // Declaração de variáveis
  
  long long int    a, b;                      // Números digitados
  int              teste1, teste2, n1, n2;    // Testes de leituras
  long long int    mmc1, mdc1;                // Mínimo múltiplo comum e máximo divisor comum
  char             *ptr1, *ptr2;              // Para testes de leituras

  // Indicação de que são precisos dois valores
 
  if (argc != 3)
    {
      printf("\nERRO: Insira dois números naturais, separados por um espaço em branco.\n");
      printf ("\n");
      return 1;
    }

  // Utilizar a função strrol, para garantir, nos testes, que os números inseridos não têm floating point (têm de ser naturais)
  
  n1 = strtol (argv [1], &ptr1, 10);
  n2 = strtol (argv [2], &ptr2, 10);

  // Leitura dos valores dados na linha de comandos
  
  teste1 = sscanf (argv [1], "%lld", &a);
  teste2 = sscanf (argv [2], "%lld", &b);

  /* Teste das leituras dos valores na linha de comandos (terão de ser números naturais)
     NOTA: declarando a e b como unsigned long long int, o programa não funcionava como esperado e admitia números inteiros negativos;
     assim, declararam-se a e b como long long int.                                                                                    */
  
  if ((teste1 == 0) || (teste2 == 0) || ((*ptr1) != 0) || ((*ptr2) != 0) || (a <= 0) || (b <= 0))
    {
      printf ("\nERRO: Insira dois números naturais, separados por um espaço em branco.\n");
      printf ("\n");
      return 2;
    }

  // Cálculo e impressão dos valores do máximo divisor comum e do mínimo múltiplo comum entre a e b

  printf ("\n*-*-*-*-* Máximo divisor comum e mínimo múltiplo comum *-*-*-*-*\n");
  
  mdc1 = mdc (a, b);
  mmc1 = mmc (a, b);

  printf ("\nO máximo divisor comum entre %lld e %lld é:   %lld \n", a, b, mdc1);
  printf ("\nO mínimo múltiplo comum entre %lld e %lld é:  %lld \n", a, b, mmc1);

  // Terminar o programa
  
  printf ("\n-FIM-\n");
  printf ("\n");

  return 0;
}
 
