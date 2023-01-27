#include <iostream>
#include <cstdlib>

using namespace std;

int* fintv (int* v, int n_int) {
  v = new int [n_int];
  return v;
}

int** fintv (int** v, int int_colunas, int int_linhas) {
  int i=0;
  v = new int* [int_linhas];
  while (i<int_linhas)
    {
      v [i] = new int [int_colunas];
      i++;
    }
  return v;
}

int*** fintv (int*** v, int int_indice1, int int_indice2, int int_indice3) {
  int i=0, j=0;
  v = new int** [int_indice3];
  while (i<int_indice3)
    {
      v [i] = new int* [int_indice2];
      while (j<int_indice2)
	{
	  v[i][j] = new int [int_indice1];
	  j++;
	}
      j=0;
      i++;
    }
  return v;
}
  
  

		       
