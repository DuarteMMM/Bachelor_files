#include "MatrixAlgorithms.h"
#include "FCmatrixFull.h"
#include <iostream>


int main() {

  double** agh = new double*[5] {new double[5]{1,2,3,4,5}, new double[5]{0,1,0,5,7},new double[5] {0,1,1,1,1}, new double[5]{0,0,0,8,8}, new double[5]{6,6,3,2,1}};
  
  FCmatrixFull matrix (agh, 5, 5);
  FCmatrixFull matrix2 (matrix);
  FCmatrixFull matrix3 (matrix);

  cout << matrix << endl;
  MatrixAlgs::GaussElimination(matrix);
  cout << matrix << endl;
  /*MatrixAlgs::DoPivotedGaussElimination(matrix2);
  cout << matrix2 << endl;*/
  cout << matrix3 << endl;
  MatrixAlgs::DoLUDecomposition(matrix3);
  cout << matrix3 << endl;

  for(int i = 0; i < 5; i++) {

    delete[] agh[i];

  }

  delete[] agh;

}
