/******************************************************
 *                Física Computacional                *
 *                      FCmatrix                      *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include "FCmatrix.h"
#include "Vec.h"

#include <vector>
#include <iostream>

using namespace std;

FCmatrix::FCmatrix() : classname("FCmatrix") {}
FCmatrix::FCmatrix(double **arrays, int m, int n) : classname("FCmatrix") {}
FCmatrix::FCmatrix(double *array, int m, int n) : classname("FCmatrix") {}
FCmatrix::FCmatrix(const vector<Vec>&) : classname("FCmatrix") {}
FCmatrix::FCmatrix(const FCmatrix &) : classname("FCmatrix") {}


ostream& operator<<(ostream& s, const FCmatrix& matrix)
{
  int N = matrix.Get_nRows();
  
  for (int i = 0; i < N; i++)
    s << matrix.M[i] << endl;

  return s;
}
