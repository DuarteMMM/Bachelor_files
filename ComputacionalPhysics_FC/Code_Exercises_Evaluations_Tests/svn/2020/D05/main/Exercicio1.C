/******************************************************
 *                Física Computacional                *
 *                    Exercício 1                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio>

// Resposta à alínea a: sim, existiam erros no programa, nomeadamente não se ter definido a função main

int addnumbers (int a, int b)
{
  int sum = 0;

  for (int i = a; i <= b; i++)
    {
      sum += i;
    }

  return sum;
}

int main ()
{
  printf ("\n-=-=-=- Soma dos números inteiros entre a e b -=-=-=-\n");
  int a, b, total;
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

  total = addnumbers (a, b);

  printf ("\nA soma de todos os inteiros entre %d (inclusive) e %d (inclusive) é %d.\n\n", a, b, total);

  return 0;
}

  

  
  
