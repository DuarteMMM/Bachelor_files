#include "EqSolver.h"
#include "FCmatrix.h"
#include "FCmatrixAlgorithms.h"
#include "Vec.h"

#include <iostream>


using namespace std;


int main() {

  double** d = new double* [3] {new double[3] {1,0,0}, new double[3] {0,1,0}, new double[3] {0,0,1}};

  FCmatrixFull matriz1 (d, 3, 3);
  double da[3] = {1,2,3};
  Vec coef (3, da);
  
  EqSolver problema1(matriz1, coef);

  cout << "Matriz: " << matriz1 << endl;
  cout << "Determinante: " << matriz1.GetDeterminant() << endl;
  cout << "Vetor de coeficientes: " << coef << endl;
  cout << "Solução: " << problema1.LUdecompositionSolver() << endl;

  cout << matriz1 << endl;
  cout << matriz1.GetDeterminant() << endl;
  
  for (int i = 0; i<3; i++) {
    delete d[i];
  }

  delete[] d;
  cout << "completed d deletion--------------------" << endl;
  
}
