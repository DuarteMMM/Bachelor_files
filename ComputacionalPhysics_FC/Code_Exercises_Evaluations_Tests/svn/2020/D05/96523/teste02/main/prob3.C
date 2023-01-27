#include <iostream>
#include "FCmatrixFull.h"
#include "ODESolver.h"
#include "TF1.h"


int main () {

  cout << "\nProblema 3\n" << endl;

  cout << "Alínea a\n" << endl;

  double L = 5;
  int pontos = 101;
  double delta_x = L/pontos;

  double delta_t = 0.01;

  double D = 1.0;

  double beta = (-D * delta_t) / (delta_x*delta_x);

  double vec_matrizA[] = {beta, 0., 0., 0., 1.-2.*beta, 0., 0., 0., beta};
  double vec_matrizB[] = {-beta, 0., 0., 0., 1+2.*beta, 0., 0., 0., -beta};

  FCmatrixFull A (vec_matrizA, 3, 3);
  FCmatrixFull B (vec_matrizB, 3, 3);

  cout << "Matriz A:\n" << A << "\n\nMatriz B:\n" << B << endl;

  cout << "Alínea b\n" << endl << endl;

  /*
  // Criar 3 equações diferenciais, com 6 variáveis no total

  TF1 f1 ("f1", [&](double* x, double* par){return -x[0];}, 0, 10, 0);
  TF1 f2 ("f2", [&, beta](double* x, double* par){return x[1]*((1+2*beta)/(1-2*beta));}, 0, 10, 0);
  TF1 f3 ("f3", [&](double* x, double* par){return -x[2];}, 0, 10, 0);
  */

  return 0;
}
