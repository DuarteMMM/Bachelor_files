#ifndef __FCmatrixAlgorithms__
#define __FCmatrixAlgorithms__

#include "FCmatrixFull.h"

using namespace std;

class FCmatrixAlgorithms
{
public:
 // Methods

  static void GaussElimination(FCmatrixFull &, int flag=0, int ifaugmented = 0); // flag=0: sem pivotagem; ifaugmented = 0: não augmented
  
  static void GaussJordan(FCmatrixFull&, FCmatrixFull&, int flag=0); // flag=0: sem pivotagem
  
  static void LUdecomposition (FCmatrixFull &); // Doolittle LU Decomposition
}; 

#endif 
