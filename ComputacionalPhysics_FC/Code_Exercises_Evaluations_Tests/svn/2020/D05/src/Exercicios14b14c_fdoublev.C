#include <iostream>
#include <cstdlib>

using namespace std;

double* fdoublev (double* v, int n_double) {
  v = (double*) malloc (n_double*sizeof(double));
  return v;
}

double** fdoublev (double** v, int double_colunas, int double_linhas) {
  int i=0;
  v = (double**) malloc (double_linhas*sizeof(double*));
  while (i<double_linhas)
    {
      v [i] = (double*) malloc (double_colunas*sizeof(double));
      i++;
    }
  return v;
}

double*** fdoublev (double ***v,int double_indice1, int double_indice2, int double_indice3) {
  int i=0, j=0;
  v= (double***) malloc (double_indice3*sizeof(double**));
  while (i<double_indice3)
    {
      v [i] = (double**) malloc (double_indice2*sizeof(double*));
      while (j<double_indice2)
	{
	  v[i][j] = (double*) malloc (double_indice1*sizeof(double));
	  j++;
	}
      j=0;
      i++;
    }
  return v;
}
  
  

		       
