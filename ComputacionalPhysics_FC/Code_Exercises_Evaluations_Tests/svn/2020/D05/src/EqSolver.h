#ifndef __EqSolver__
#define __EqSolver__

#include "FCmatrixFull.h"

using namespace std;

class EqSolver
{
private:
  FCmatrixFull M;    // Matriz Full
  Vec b, x;   // Vetores das constantes, das soluções
  
// Se matrix já foi resolvida de uma dada maneira
  bool isLUSolved; 
  bool isGaussSolved; 
  
  int isAugmented; // Se matriz é aumentada (1) ou não (0)
  
  bool canSolve; // Se a matriz impede o sistema de ser determinado
  
public:
  // Construtores
  EqSolver();
  EqSolver(const FCmatrixFull &, const Vec &); // Para matrizes não aumentadas
  EqSolver(const FCmatrixFull &); // Para matrizes aumentadas

  // Sets
  void SetConstants(const Vec &);
  void SetMatrix(const FCmatrixFull &);
  void ShowMatrix();
  FCmatrixFull GetMatrix();
  void Showb();
  Vec Getb();
  void Showx();
  Vec Getx(); // Este método é irrelevante, porque x é o que vem das resoluções

  // Resolver
  Vec GaussEliminationSolver(int flag=0); // flag=0: sem pivotagem
  Vec LUdecompositionSolver();
  // Iterators; IfWeighting=0 -> não é feito weighting
  Vec JacobiIterator(Vec, int&, double tol=1.e-4, int IfWeighting=0);
  Vec GaussSeidelIterator(Vec, int&, double tol=1.e-4, int IfWeighting=0);
};

#endif
