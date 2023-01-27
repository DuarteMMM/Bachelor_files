#include <iostream>
#include <cstdlib>

using namespace std;

int* fintv (int n_int, int* v) {
  v =  (int*) malloc(n_int*sizeof(int));
  return v;
}
