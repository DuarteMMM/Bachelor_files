/******************************************************
 *                Física Computacional                *
 *                    Exercício 7                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio>

int addsquares_int (int a, int b)
{
  int soma = 0;

  for (int i = a; i <= b; i++)
    {
      soma += i*i;
    }

  return soma;
}

double addsquares_double (int a, int b)
{
  double soma = 0;

  for (int i = a; i <= b; i++)
    {
      soma += i*i;
    }

  return soma;
}

int main ()
{
  printf ("\n-=-=-=- Soma dos quadrados dos números inteiros entre a e b -=-=-=-\n");
  int a, b, total_int;
  double total_double;
  int teste_a = 0, teste_b = 0, valor_para_troca;

  printf ("\nDigite o valor de a:\n");
  teste_a = scanf ("%d", &a);

  if (teste_a != 1)
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }

  printf ("\nDigite o valor de b:\n");
  teste_b = scanf ("%d", &b);

  if (teste_b != 1)
    {
      printf ("\nDigitou algo inválido.\n");
      return 2;
    }

  // Trocar a ordem, se necessário
  
  if (b < a)
    {
      valor_para_troca = a ;
      a = b;
      b = valor_para_troca;
    }

  total_int = addsquares_int (a, b);
  printf ("\nA soma de todos os quadrados dos números inteiros entre %d (inclusive) e %d (inclusive), em int, é %d.\n\n", a, b, total_int);

  total_double = addsquares_double (a, b);
  printf ("\nA soma de todos os quadrados dos números inteiros entre %d (inclusive) e %d (inclusive), em double, é %.0lf.\n\n", a, b, total_double);

  return 0;
}

/*Comparação entre o  valor em int e o valor em double para a=1 e b=5000:

Com int, o resultado é total_int=-1270505460.
Com double, o resultado é total_double=41679167500 (o valor verdadeiro da soma de quadrados em causa).

Ora, os valores mínimo e máximo que se podem representar, em int, em C++, são, respetivamente:
INT_MAX = 2147483647 ;
INT MIN = -2147483648.

Ao dividir total_double por INT_MAX, verifica-se que dá 19.4... Começando no zero, total_int acaba por igualar INT_MAX, e depois "passa" para INT_MIN e começa a somar a partir daí, efetuando estes "ciclos" sucessivos: o total "percorre" 19 "caminhos", sendo cada "caminho" ir do 0 ao INT_MAX ou do INT_MIN ao 0. Cada caminho corresponde à passagem por |INT_MIN| números (o caminho não negativo inclui o zero, daí INT_MAX < |INT_MIN|).

Assim, fazemos total_double - 19*|INT_MIN| = 876978188 (o que resta "percorrer"). O total estará agora num número negativo, logo parará em INT_MIN + 876978188 = -1270505460, exatamente o valor apresentado para total_int ! */


