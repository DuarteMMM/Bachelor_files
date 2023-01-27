#include <iostream>
#include <cstdlib>

using namespace std;

double* fdoublev (int n_double, double* v) {
  v = (double*) malloc (n_double*sizeof(double));
  return v;
}
