/******************************************************
 *                Física Computacional                *
 *                     Exercício 24                   *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream>  // cout
#include <cstdio>    // printf
#include <vector>
#include <cstdlib>   // rand(), RAND_MAX
#include <cmath>     // pow, sqrt
#include <numeric>   // accumulate
#include <algorithm> // for_each
using namespace std;

int main ()
{
  cout << "\n-=-=-=-=-=- Exercício 24 -=-=-=-=-=-" << endl;
  vector<double>v(100);
  int contador=0;
  srand (time(NULL));
  while (contador < 100)
    {
      v[contador]=((double)rand())/((double)RAND_MAX);
      contador++;
    }
  contador=0;

  // Soma total e média (alínea a)
  
  double sum = accumulate (v.begin(), v.begin()+100, 0.0); // Soma de todos os valores
  double media = sum/100.;
  printf ("\nA soma dos valores gerados é de, aproximadamente, %.3lf. A média é de %.5lf.\n", sum, media);

  // Desvio-padrão (alínea b)

  double var = 0.;
  for_each (v.begin(), v.end(), [&var, media](int x){
				  var+=pow(x-media, 2.); // x dá o valor do vetor
				});
  var /= 99.; // A fórmula tem n-1 no denominador, não n
  cout << "\nO desvio padrão é de, aproximadamente, " << sqrt(var) << ".\n" << endl;

  // Obter amostra de média nula: decidi tornar cada número o simétrico do anterior (alínea c)

  while (contador < 100)
    {
      if (contador % 2 == 1)
	v[contador]=(-1)*v[contador-1];
      contador++;
    }
  contador=0;

  sum = accumulate (v.begin(), v.begin()+100, 0.0);
  media = sum/100.;
  printf (" *** *** *** *** ***\n\nA nova média (alínea c) é, de facto, %.1lf.\n\n", media);

  // Ordenar por ordem crescente e determinar as diferenças consecutivas (alínea d)

  sort (v.begin(), v.end());
  
  cout << "As sucessivas diferenças entre os valores (ordenados) são, aproximadamente:\n" << endl;
  while (contador<99)
    {
      printf ("%lf   ", v[contador+1]-v[contador]);
      contador++;
    }

  cout << "\n\n -FIM-\n" << endl;
  v.clear();  

  return 0;
}
