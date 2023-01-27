#ifndef __matrixalgs__
#define __matrixalgs__


#include "FCmatrixFull.h"


class MatrixAlgs {

 public:

  static void DoGaussElimination (FCmatrixFull&); //pôr vetor de índices?
  /*
    - can receive simple matrix
    - linear systems: (a | b)
    - return: (a | b | index) -> index por causa da pivotagem
   */

  
  static void DoPivotedGaussElimination (FCmatrixFull&);

  
  static void DoLUDecomposition (FCmatrixFull&);

};



#endif
