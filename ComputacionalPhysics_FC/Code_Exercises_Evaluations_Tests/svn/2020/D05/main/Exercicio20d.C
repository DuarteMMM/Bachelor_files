/******************************************************
 *                Física Computacional                *
 *                    Exercício 20d                   *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include <iostream>
using namespace std;

int main ()
{
  int contador_n=0, contador_Z=0;
  double k = 2.179e-18;

  double E[10][20];
  
  auto matrix = [k] (int n, int Z) -> double
		{
		  double Energia = (-k*Z*Z)/(n*n);
		  return Energia;
		};
  
  while (contador_Z < 10)
    {
      while (contador_n < 20)
	{
	  E[contador_Z][contador_n] = matrix (contador_n+1, contador_Z+1);
	  contador_n++;
	}
      contador_n=0;
      contador_Z++;
    }

  cout << "\nO programa foi executado com sucesso.\n" << endl;

  return 0;
}
