#include "Exercicio40_GetRandom.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

double GetRandom (double xmin, double xmax)
{
  double numero1, numero2, numero3, numero4;
  srand (time(NULL));
  numero1 = (double)(rand()) / (double)(RAND_MAX); // Número entre 0 e 1
  if ( (xmin < 0.00001) && (xmax < 0.00001) )
    {
      // Por exemplo, entre -35 e -20
      numero2 = abs(xmax) - abs(xmin); // 15
      numero3 = numero1*numero2; // Entre -15 e 0
      numero4 = numero3+xmax; // Entre -35 e -20
    }

  if ( (xmin > 0.00001) && (xmax > 0.00001) )
    {
      // Por exemplo, entre 20 e 35
      numero2 = xmax - xmin; // 15
      numero3 = numero1*numero2; // 0 e 15
      numero4 = numero3+xmin; // 20 e 35
    }

  if ( (xmin < 0.00001) && (xmax > 0.00001) )
    {
      // Por exemplo, entre -20 e 35
      numero2 = xmax - xmin; // 55
      numero3 = numero1*numero2; // 0 e 55
      numero4 = numero3 + xmin; // -20 e 35
    }
  return numero4;
}
