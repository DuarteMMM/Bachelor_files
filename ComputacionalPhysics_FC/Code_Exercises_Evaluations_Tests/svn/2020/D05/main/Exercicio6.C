/******************************************************
 *                Física Computacional                *
 *                    Exercício 6                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream> // cout
#include <cstdlib>  // atoi
#include <cstdio>  // printf
using namespace std;

// Protótipo

int square (int x);


int main (int argc, char* argv[] )
{
  printf ("\nDigite um número inteiro positivo cujo quadrado deseja saber: ");
  int N, teste_N;
  teste_N = scanf ("%d", &N);

  if ( (teste_N != 1) || (N<=0) )
    {
      printf ("\nERRO: Não digitou um valor inteiro positivo.\n\n");
      return 1;
    }
  
  printf("\nTem-se que: %d^2 = %d\n\n", N, square(N));
}

// Definir a função de acordo com as imposições do enunciado

int square (int x) {
  if (x==1) {   // condição base (fim da recorrência ou se N=1)
    return 2*(x-1)+1;
  } else { // recorrência
    return square(x-1)+2*(x-1)+1;
  }
}

/* Como se definiu a recorrência (calcular a partir de (x-1)^2):

x^2 = (x-1+1)^2 = (x-1)^2 + 1 + 2(x-1)
Tem de se pôr a condição de fim, a condição base, para quando N=1 (o quadrado é 1) ou para terminar a recorrência: termina-se o "ciclo", multiplicando por 1.
*/
