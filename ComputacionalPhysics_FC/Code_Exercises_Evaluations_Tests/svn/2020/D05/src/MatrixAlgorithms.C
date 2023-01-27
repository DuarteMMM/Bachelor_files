#include "MatrixAlgorithms.h"
#include "FCmatrixFull.h"
#include "Vec.h"

#include <iostream>

#define TOLERANCE 1e-07
#define DEBUG

void MatrixAlgs::DoGaussElimination(FCmatrixFull& matrix) {

  int nrows = matrix.Get_nRows();
  
  for (int i = 0; i < nrows - 1; ++i) {
    for (int j = (i+1); j < nrows; ++j) {
      double coef = (-1.)*matrix[j][i] / matrix[i][i];
      for (int k = i; k < nrows; ++k) {
	matrix[j][k] += (matrix[i][k] * coef);
      }
    }
  }
}


void MatrixAlgs::DoPivotedGaussElimination(FCmatrixFull& matrix) {

  int nrows = matrix.Get_nRows();
  vector<double> maximums;
  
  for (int i = 0; i < nrows - 1; ++i) {

    maximums.push_back(matrix[i].max());
#ifdef DEBUG
    if (matrix[i].max() == 0) {
      cout << "Warning: Singular Matrix in Gauss Elimination\n";
    }
#endif
  }

  //eliminação de gauss - confirmar como funciona o GetRowN()
  for (int i = 0; i < nrows - 1; ++i) {

    double pivot = matrix[i][i];
    double pivotsize = matrix[i][i] / maximums[i];
    double pivotrow = i;
    
    for(int j = i; j < nrows; ++j) {

      if ((matrix[j][i]/maximums[j]) > pivotsize) {

	pivot = matrix[j][i];
	pivotsize = matrix[j][i]/maximums[j];
	pivotrow = j;
	
      }
    }

    if (pivotrow != i) {

      matrix.swapRows(i, pivotrow);

    }
    
    for(int k = i+1; k < nrows; ++k) {
      
      double coef = (-1.)*matrix[k][i] / pivot;
      matrix[k] += (matrix[i] * coef);

    }
      
  }

}



void MatrixAlgs::DoLUDecomposition(FCmatrixFull& matrix) {

  int nrows = matrix.Get_nRows();

  //eliminação de gauss - confirmar como funciona o GetRowN()
  for (int i = 0; i < nrows - 1; ++i) {
    
    for(int j = (i+1); j < nrows; ++j) {

      double coef = (-1.)*matrix[j][i] / matrix[i][i];
      //matrix[j] += (matrix[i] * coef);
      for (int k = i; k < nrows; ++k) {
	matrix[j][k] += (matrix[i][k] * coef);
      }
	    
      matrix[j][i] = (-1.)*coef;
      
    }

    cout << matrix << endl;
  }
}
