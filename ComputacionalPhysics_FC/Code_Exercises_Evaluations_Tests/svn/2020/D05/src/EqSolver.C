/******************************************************
 *                Física Computacional                *
 *                      EqSolver                      *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "EqSolver.h"
#include "FCmatrixAlgorithms.h"

#include <algorithm> // find, distance
#include <iostream>

#include "TString.h"
#include "TMath.h"

#define TOLERANCE 1.e-100

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
}


EqSolver::EqSolver(const FCmatrixFull &matriz_Full, const Vec &vetor_b)
{
  M = matriz_Full;
  b = vetor_b;

  isLUSolved = false;
  isGaussSolved = false;

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

  b = M.RemoveLastCol();
  
  isLUSolved = false;
  isGaussSolved = false;

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

      b = M.RemoveLastCol();
    
      Vec diag_principal = M.Get_MidDiag();
      const int size_diag = diag_principal.size();

      const int n1 = M.Get_nCols() - 1;
      const int m1 = m - 1;
    
      for (int k=0; k < size_diag; k++)
	{
	  if (abs(diag_principal[k]) < TOLERANCE) {
	    
	    throw invalid_argument(TString::Format("[%s] received undetermined system 1...!\n", __PRETTY_FUNCTION__));
	  }

	}

      x = b;

      if (canSolve == true)
	{
	  for (int i = n1; i >= 0; i--)
	    {
	      for (int j = m1; j > i; j--)
		x[i] -= M[i][j] * x[j];

	      x[i] = x[i] / M[i][i];
	    }
	  isGaussSolved = true;
	}
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


// Jacobi method
// Em max, será retornado o número de iterações
Vec EqSolver::JacobiIterator (Vec InitialGuess, int& max, double tol, int IfWeighting) {
  
  int n = M.Get_nRows();
  int m = M.Get_nCols();
  
  if (isGaussSolved == false && isLUSolved == false && InitialGuess.size() == m && n == m) {
    
    int verify = 1; // Verifica se já se alcançou a tolerância desejada (tol)
    bool DiagDom = M.IsDiagonallyDominant();
    int iter = 0; // Number of iterations

    // Com Weighting
    double omega, delta_x_k, delta_x_kp;
    // Valores passíveis de serem mudados mediante resultados obtidos
    int k = 10;
    int p = 30;

    // Vetores com os valores de x: iteração atual e iteração seguinte
    vector<double> current (InitialGuess.GetEntries(), InitialGuess.GetEntries() + m);
    vector<double> next(m);

    // Preencher o vetor next para um número de iterações inferior ou igual a max
    
    while (iter < max) {

      // Avançar nas linhas (entradas de next)
      for (int i=0; i<n; i++) {

	next[i] = 0; // Repor valor nulo no vetor
	
	for (int j=0; j<m; j++) {
	  if (i!=j)
	    next[i] -= M[i][j]*current[j];
	}

	next[i] += b[i];

	if (IfWeighting == 0 || iter <= k+p)
	  next[i] *= 1./M[i][i];

	if (IfWeighting != 0 && iter > k+p)
	  next[i] = next[i] * (omega / M[i][i]) + (1.-omega)*current[i];

	// Verificar se já se alcançou <tol para esta entrada i
	if (verify == 1 && abs(next[i]-current[i]) > tol)
	  verify = 0;

      }

      // Se em nenhum elemento x_i se tiver dado verify=0, já se satisfaz tol para todos os elementos do vetor x
      if (verify == 1)
	break;

      verify = 1; // Para o próximo ciclo

      // Calcular o vetor delta_x_k para cálculos com Weighting
      if (IfWeighting != 0 && iter == k) {
	for (int contador=0; contador<m; contador++)
	  delta_x_k += (current[contador]-next[contador]) * (current[contador]-next[contador]);
	delta_x_k = sqrt (delta_x_k);
      }

      
      // Calcular o vetor delta_x_kp e omega para cálculos com Weighting
      if (IfWeighting != 0 && iter == k+p) {
	for (int contador2=0; contador2<m; contador2++)
	  delta_x_kp += (current[contador2]-next[contador2]) * (current[contador2]-next[contador2]);
	delta_x_kp = sqrt (delta_x_kp);

	omega = 2. / (1. + sqrt (1. - pow (delta_x_kp/delta_x_k, 1./p) ) );
      }

	
      // Mudar o vetor iteração atual
      current=next;

      // Avançar para próximo ciclo
      iter++;
    }
    
    if (iter == max) {
      if (DiagDom == false)
	throw invalid_argument (TString::Format("[%s]: the matrix is not diagonally dominant; the maximum number of iterations has been reached.\n", __PRETTY_FUNCTION__));
      else
	throw invalid_argument (TString::Format("[%s]: the maximum number of iterations has been reached.\n", __PRETTY_FUNCTION__));
    }

    max = iter; // Retornar em max o número de iterações
    
    return Vec(m, current.data());
      
  }

  else {
    if (n != m)
      throw invalid_argument (TString::Format("[%s]: the matrix must be square.\n", __PRETTY_FUNCTION__));
      
    if (InitialGuess.size() != m)
      throw invalid_argument (TString::Format("[%s]: the Vec received has a number of elements incompatible with the matrix.\n", __PRETTY_FUNCTION__));

    if (isLUSolved == true)
      throw invalid_argument (TString::Format("[%s]: the matrix has already been LU solved...\n", __PRETTY_FUNCTION__));

    if (isGaussSolved == true)
      throw invalid_argument (TString::Format("[%s]: the matrix has already been subjected to Gauss Elimination...", __PRETTY_FUNCTION__));

    return Vec();
  }
}



// Gauss-Seidel method
// Em max, será retornado o número de iterações
Vec EqSolver::GaussSeidelIterator (Vec InitialGuess, int& max, double tol, int IfWeighting) {

  int n = M.Get_nRows();
  int m = M.Get_nCols();
  
  if (isGaussSolved == false && isLUSolved == false && InitialGuess.size() == m && n == m) {

    int verify = 1;
    bool DiagDom = M.IsDiagonallyDominant();
    int iter = 0;

    double omega, delta_x_k, delta_x_kp;
    int k = 10;
    int p = 30;

    vector<double> current (InitialGuess.GetEntries(), InitialGuess.GetEntries() + m);
    vector<double> next(m);
    
    while (iter < max) {

      for (int i=0; i<n; i++) {

	next[i] = 0;
	
	// É aqui que difere do método de Jacobi: usam-se, quando possível, valores das novas iterações para os cálculos
	for (int j=0; j<m; j++) {
	  if (j < i)
	    next[i] -= M[i][j]*next[j];
	  if (j > i)
	    next[i] -= M[i][j]*current[j];
	}

	next[i] += b[i];

	if (IfWeighting == 0 || iter <= k+p)
	  next[i] *= 1./M[i][i];

	if (IfWeighting != 0 && iter > k+p)
	  next[i] = next[i] * (omega / M[i][i]) + (1.-omega)*current[i];

	if (verify == 1 && abs(next[i]-current[i]) > tol)
	  verify = 0;

      }

      if (verify == 1)
	break;

      verify = 1;

      if (IfWeighting != 0 && iter == k) {
	for (int contador=0; contador<m; contador++)
	  delta_x_k += (current[contador]-next[contador]) * (current[contador]-next[contador]);
	delta_x_k = sqrt (delta_x_k);
      }

      if (IfWeighting != 0 && iter == k+p) {
	for (int contador2=0; contador2<m; contador2++)
	  delta_x_kp += (current[contador2]-next[contador2]) * (current[contador2]-next[contador2]);
	delta_x_kp = sqrt (delta_x_kp);

	omega = 2. / (1. + sqrt (1. - pow (delta_x_kp/delta_x_k, 1./p) ) );
      }

      current=next;

      iter++;
    }
    
    if (iter == max) {
      if (DiagDom == false)
	throw invalid_argument (TString::Format("[%s]: the matrix is not diagonally dominant; the maximum number of iterations has been reached.\n", __PRETTY_FUNCTION__));
      else
	throw invalid_argument (TString::Format("[%s]: the maximum number of iterations has been reached.\n", __PRETTY_FUNCTION__));
    }

    max = iter;
    
    return Vec(m, current.data());
      
  }

  else {
    if (n != m)
      throw invalid_argument (TString::Format("[%s]: the matrix must be square.\n", __PRETTY_FUNCTION__));
      
    if (InitialGuess.size() != m)
      throw invalid_argument (TString::Format("[%s]: the Vec received has a number of elements incompatible with the matrix.\n", __PRETTY_FUNCTION__));

    if (isLUSolved == true)
      throw invalid_argument (TString::Format("[%s]: the matrix has already been LU solved...\n", __PRETTY_FUNCTION__));

    if (isGaussSolved == true)
      throw invalid_argument (TString::Format("[%s]: the matrix has already been subjected to Gauss Elimination...", __PRETTY_FUNCTION__));

    return Vec();
  }
}
