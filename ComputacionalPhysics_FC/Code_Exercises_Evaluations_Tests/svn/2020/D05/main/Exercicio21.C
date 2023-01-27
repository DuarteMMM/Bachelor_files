/******************************************************
 *                Física Computacional                *
 *                    Exercício 21                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime> // srand (time(NULL))
using namespace std;

vector<double> rand2vec (int n)
{
  vector<double> v(n);
  int i=0;
  while (i<n)
    {
      double f = ((double)rand() / (double)RAND_MAX)*360.0;
      v [i] = f;
      i++;
    }
  return v;
}


int main ()
{
  int n, teste_n;
  printf ("\nQuantos valores aleatórios deseja gerar? \n");
  teste_n = scanf ("%d", &n);
  if ( (teste_n != 1) || (n < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }
  srand (time (NULL));
  vector<double> v(n);
  v = rand2vec (n);
  
  v.clear(); // Limpar o vetor

  printf ("\nO programa foi executado corretamente.\n\n");
  return 0;
}
