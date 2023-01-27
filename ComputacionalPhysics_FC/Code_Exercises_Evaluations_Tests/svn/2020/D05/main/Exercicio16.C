/******************************************************
 *                Física Computacional                *
 *                    Exercício 16                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include <iostream>
using namespace std;

void sum (const double* const v, int n);

// Função que permite retornar a soma no 1º elemento do array

double* sum2 (double* v, int n) {
  int i=0;
  double soma=0.;
  while (i<n)
    {
      soma+=v[i];
      i++;
    }
  v[0]=soma;
  return v;
}

int main ()
{
  double* array_exemplo = (double*)malloc(5*sizeof(double));
  for (int i=0; i<5; i++)
    array_exemplo[i]=(double)(i);
  sum (array_exemplo, 5);
  array_exemplo = sum2 (array_exemplo, 5);
  cout << "O valor da soma é " << array_exemplo [0] << "." << endl;
  free (array_exemplo);
  return 0;
}

void sum (const double* const v, int n) {
  int i=0;
  double soma;
  while (i<n)
    {
      soma+=v[i];
      i++;
    }
}

// Não é possível retornar a soma dos elementos no 1º elemento do array porque o array é passado para a função sum como "const"
