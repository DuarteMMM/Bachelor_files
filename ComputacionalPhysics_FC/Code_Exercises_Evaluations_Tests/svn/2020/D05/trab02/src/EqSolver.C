/******************************************************
 *                Física Computacional                *
 *                      EqSolver                      *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "EqSolver.h"
#include "FCmatrixAlgorithms.h"
//#include "FCtools.h"

#include <algorithm> // find, distance
#include <iostream>

#include "TString.h"
#include "TMath.h"

#define TOLERANCE 1.e-100
#define LOG_TOLERANCE -1000

//#define DEBUG
using namespace std;

/////////////////////////// Construtores

// Default Constructor
EqSolver::EqSolver()
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  isGaussSolved = false;
  canSolve = false;
  //isAugmented = 0;
}


EqSolver::EqSolver(const FCmatrixFull &matriz_Full, const Vec &vetor_b)
{
  M = matriz_Full;
  b = vetor_b;

  isLUSolved = false;
  isGaussSolved = false;
  //isAugmented = 0;

  if (M.Get_nRows() >= M.Get_nCols()) {
    
    canSolve = true; // Embora na verdade possa ou não ser resolvível
    
  } else {
    
    canSolve = false;
    cout << "Cant solve" << endl;
  }
}

EqSolver::EqSolver(const FCmatrixFull &matriz_Full)
{
  M = matriz_Full;

  //FCmatrixFull Copia(M);
  //b = Copia.RemoveLastCol();

  b = M.RemoveLastCol();
  
  isLUSolved = false;
  isGaussSolved = false;
  //isAugmented = 1;

  /*if (Copia.Get_nRows() >= Copia.Get_nCols())
    canSolve = true; // Embora na verdade possa ou não ser resolvível

  else
  canSolve = false;*/

  if (M.Get_nRows() >= M.Get_nCols())
    canSolve = true; // Embora na verdade possa ou não ser resolvível

  else
    canSolve = false;
  
}


///////////////////////////////////Prints and Getters


void EqSolver::ShowMatrix()
{
  cout << M << endl;
}


FCmatrixFull EqSolver::GetMatrix()
{
  return M;
}


void EqSolver::Showb()
{
  cout << b << endl;
}


Vec EqSolver::Getb()
{
  return b;
}


void EqSolver::Showx()
{
  cout << x << endl;
}


Vec EqSolver::Getx()
{
  return x;
}


/*void EqSolver::ShowIndex()
{
  cout << index << endl;
}


Vec EqSolver::GetIndex()
{
  return index;
}


int EqSolver::PosOfIndex(double indice)
{
  int n = M.Get_nRows();
  double* vetor_index = index.GetEntries();
  auto itr = find (vetor_index, vetor_index + n, indice);
 
  if (itr != vetor_index + n)
    return distance(vetor_index, itr);

  else {
    cout << __PRETTY_FUNCTION__ << ": Element is not present.\n";
    return n;
  }

  delete[]vetor_index;
  }*/
  

///////////////////////////////////////Setters


// Set Vector of Constants, b
void EqSolver::SetConstants(const Vec &vetor_b)
{
  b = vetor_b;
  isGaussSolved = false;
  isLUSolved = false;
}


// Set Coeficients Matrix Full não aumentada!
void EqSolver::SetMatrix(const FCmatrixFull &matriz_Full)
{
  M = matriz_Full;

  isLUSolved = false;
  isGaussSolved = false;
  //isAugmented = 0;

  if (M.Get_nRows() >= M.Get_nCols())
    canSolve = true;

  else
    canSolve = false;
}



//////////////////////////////////// Solvers


//Gauss Elimination Solver
Vec EqSolver::GaussEliminationSolver(int flag)
{
  if (isGaussSolved == false && canSolve == true && isLUSolved == false)
    {      
   
      M.Augment(b);
      FCmatrixAlgorithms::GaussElimination(M, flag, 1);

#ifdef DEBUG
      cout << M << endl;
#endif
      
      const int m = M.Get_nRows();

      //index = M.RemoveLastCol();
      b = M.RemoveLastCol();
    
      Vec diag_principal = M.Get_MidDiag();
      const int size_diag = diag_principal.size();

      //double produto = 1.;
      //double log10_produto = 0.;

      const int n1 = M.Get_nCols() - 1;
      const int m1 = m - 1;
    
      for (int k=0; k < size_diag; k++)
	{
	  //produto *= diag_principal[k];
	  //log10_produto += TMath::Log10(abs(diag_principal[k]));
	  
	  if (abs(diag_principal[k]) < TOLERANCE) {
	    
	    //k = size_diag; // Parar o ciclo
	    throw invalid_argument(TString::Format("[%s] received undetermined system 1...!\n", __PRETTY_FUNCTION__));
	  }
	  
	  //cout << fixed << setprecision(50) << "Produto: " << log10_produto << endl;
	  //cout << "Log10 diag: " << TMath::Log10(abs(diag_principal[k])) << endl;
	}

      /*if (abs(produto) < TOLERANCE)
	{
	  if(log10_produto < LOG_TOLERANCE) {
	    canSolve == false; // Se o produto é ~zero, a matriz tem 0 ou inf sols
	    //cout << "Log10(produto): " << TMath::Log10(produto) << endl;
	    //cout << "Diagonal da eliminada:" << diag_principal << endl;

	    throw invalid_argument(TString::Format("[%s] received undetermined system 1...!\n", __PRETTY_FUNCTION__));
	  }
	  }*/

      x = b;

      //cout << "x: " << x << endl;
    
      if (canSolve == true)
	{
	  for (int i = n1; i >= 0; i--)
	    {
	      for (int j = m1; j > i; j--)
		x[i] -= M[i][j] * x[j];

	      //cout << "i: " << i << endl;
	      //cout << "x[i] :" << x[i] << "M[i][i] :" << M[i][i] << endl;
	      x[i] = x[i] / M[i][i];
	      //cout << "x[i] :" << x[i] << endl;
	    }
	  isGaussSolved = true;
	}
    
      /* if (isAugmented == 1)
	 M.Augment(b);*/

      //M.Augment(index);
    }

  if (canSolve == false)
    throw invalid_argument(TString::Format("[%s] received undetermined system 2...!\n", __PRETTY_FUNCTION__));

  if (isLUSolved == true)
    throw invalid_argument(TString::Format("[%s]: the matrix has already been subjected to LU decomposition...\n", __PRETTY_FUNCTION__));

  return x;
}

// LU Decomposition Solver
Vec EqSolver::LUdecompositionSolver()
{
  if (isAugmented == 1)
    b = M.RemoveLastCol();
  
  if (M.Get_nRows() == M.Get_nCols() && isGaussSolved == false && isLUSolved == false)
    {
      int i, j;
      int n = M.Get_nCols();
      FCmatrixAlgorithms::LUdecomposition(M);
      //index = M.RemoveLastCol();

      double *solucao_y;
      solucao_y = new double[n];

      double *solucao_x;
      solucao_x = new double[n];

      for (i = 0; i < n; ++i)
	{
	  solucao_y[i] = b[i];
	  for (j = 0; j < i; ++j)
	    {
	      solucao_y[i] -= M[i][j] * solucao_y[j];
	    }
	}

      for (i = n - 1; i >= 0; --i)
	{
	  solucao_x[i] = solucao_y[i];
	  for (j = i + 1; j < n; ++j)
	    {
	      solucao_x[i] -= M[i][j] * solucao_x[j];
	    }
	  solucao_x[i] = solucao_x[i] / M[i][i];
	}

      Vec x (n, solucao_x);

      delete[] solucao_y;
      delete[] solucao_x;

      isLUSolved = true;

      //M.Augment(index);

      return x;
    }

  else {
    if (M.Get_nRows() != M.Get_nCols())
      throw invalid_argument(TString::Format("[%s]: the LU decomposition only applies to square matrices\n", __PRETTY_FUNCTION__));

    if (isLUSolved == true)
      throw invalid_argument (TString::Format("[%s]: the matrix has already been LU solved...\n", __PRETTY_FUNCTION__));

    if (isGaussSolved == true)
      throw invalid_argument (TString::Format("[%s]: the matrix has already been subjected to Gauss Elimination...", __PRETTY_FUNCTION__));

    return x;
  }
}
