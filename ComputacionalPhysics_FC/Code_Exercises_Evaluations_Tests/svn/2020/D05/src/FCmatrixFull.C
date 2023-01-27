/******************************************************
 *                Física Computacional                *
 *                    FCmatrixFull                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include "FCmatrixFull.h"
#include "FCmatrixAlgorithms.h"
//#include "FCtools.h"

#include <stdexcept>
#include <cstdio>
#include <iostream>

#include "TString.h"

#define TOLERANCE 1.e-06

//#define DEBUG
using namespace std;


// Constructors

// Construtor 1: matriz vazia
FCmatrixFull::FCmatrixFull()
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  M.push_back(Vec());
  classname = "FCmatrixFull";
}

// Construtor 2: com double**, número de linhas, número de colunas
FCmatrixFull::FCmatrixFull(double **array_M, int m, int n)
{
  if (!array_M)
    {
      cout << "\nERRO: Argumento(s) inválido(s) dado(s) à função " << __PRETTY_FUNCTION__ << "\n" << endl;
      M.push_back(Vec());
    }


  // m é número de linhas
  else
    for (int i = 0; i < m; ++i)
      M.push_back(Vec(n, array_M[i])); // Criar cada linha (que é Vec)

  classname = "FCmatrixFull";
}

// Construtor 3: com double*, número de linhas, número de colunas
FCmatrixFull::FCmatrixFull(double *array, int m, int n)
{
  if (!array)
    {
      throw invalid_argument(TString::Format("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
    }

  else
    for (int i = 0; i < m; i++)
      M.push_back(Vec(n, &array[i * n]));

  classname = "FCmatrixFull";
}

// Construtor 4: com vector<Vec>
FCmatrixFull::FCmatrixFull(vector<Vec> VetorVecs)
{
  M = VetorVecs; // Já é a própria matriz

  classname = "FCmatrixFull";
}

// Copy Constructor
FCmatrixFull::FCmatrixFull(const FCmatrixFull &matriz)
{
  M = matriz.M;

  classname = "FCmatrixFull";
}

// Operadores

// Retornar a linha com índice i (i>=0)
Vec &FCmatrixFull::operator[](int i)
{
  if (i < 0 || i >= Get_nRows())
    {
      cout << "\nERRO: Aceder a memória não alocada em " << __PRETTY_FUNCTION__ << "\n"  << endl;
      return M[0];
    }

  return M[i];
}

// Copy Assignement
FCmatrixFull FCmatrixFull::operator=(const FCmatrix &matriz)
{
  
  if (this != &matriz)
    {
      M.clear();

      const int N = matriz.Get_nRows();

      for (int i = 0; i < N; i++)
	M.push_back(matriz.GetRow(i));
    }

  return *this;
}

// Soma
FCmatrixFull FCmatrixFull::operator+(const FCmatrix &matriz) const
{
  const int N = Get_nRows();

  if (N != matriz.Get_nRows() || Get_nCols() != matriz.Get_nCols())
    {
      cout << "\nERRO: Operação inválida em " << __PRETTY_FUNCTION__ << "\n" << endl;
      return FCmatrixFull(); // Retornar matriz sem nada
    }

  vector<Vec> Sum;

  for (int i = 0; i < N; i++)
    Sum.push_back(GetRow(i) + matriz.GetRow(i)); // Operação soma para Vecs

  return Sum;
}

// Subtração
FCmatrixFull FCmatrixFull::operator-(const FCmatrix &matriz) const
{
  const int N = Get_nRows();

  if (N != matriz.Get_nRows() || Get_nCols() != matriz.Get_nCols())
    {
      cout << "\nERRO: Operação inválida em " << __PRETTY_FUNCTION__ << "\n" << endl;
      return FCmatrixFull();
    }

  vector<Vec> Dif;

  for (int i = 0; i < N; i++)
    Dif.push_back(GetRow(i) - matriz.GetRow(i));

  return Dif;
}

// Multiplicação de matrizes
FCmatrixFull FCmatrixFull::operator*(const FCmatrix &matriz) const
{
  if (Get_nCols() != matriz.Get_nRows())
    {
      cout << "\nERRO: Operação inválida em " << __PRETTY_FUNCTION__ << "\n" << endl;
      return FCmatrixFull();
    }

  const int n = Get_nRows();
  const int m = matriz.Get_nCols();

  vector<Vec> Prod;
  double *Line = new double[m];

  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
	Line[j] = GetRow(i).dot(matriz.GetCol(j));

      Prod.push_back(Vec(m, Line));
    }

  delete[] Line;

  return Prod;
}

// Multiplicar matriz por escalar
FCmatrixFull FCmatrixFull::operator*(double fator) const
{
  const int N = Get_nRows();

  vector<Vec> Prod;

  for (int i = 0; i < N; i++)
    Prod.push_back(fator * GetRow(i)); // Usa a multiplicação da classe Vec

  return Prod;
}

// Multiplicar matriz por Vec
Vec FCmatrixFull::operator*(const Vec &Obj) const
{
  const int N = Get_nRows();

  if (Get_nCols() != Obj.size())
    {
      cout << "\nERRO: Operação inválida em " << __PRETTY_FUNCTION__ << "\n" << endl;
      return Vec();
    }

  double *Prod = new double[N];

  for (int i = 0; i < N; i++)
    Prod[i] = GetRow(i).dot(Obj);

  Vec Result(N, Prod);

  delete[] Prod;

  return Result;
}

// Outros métodos

// Número de linhas
int FCmatrixFull::Get_nRows() const
{
  return M.size();
}

// Número de colunas
int FCmatrixFull::Get_nCols() const
{
  return M[0].size();
}

// Get Row
Vec FCmatrixFull::GetRow(int i) const
{
  if (i < 0 || i >= Get_nRows())
    {
      cout << "\nERRO: Aceder a memória não alocada em " << __PRETTY_FUNCTION__ << "\n"  << endl;
      return Vec();
    }

  return M[i];
}

// Get Column
Vec FCmatrixFull::GetCol(int j) const
{
  if (j < 0 || j >= Get_nCols())
    {
      cout << "\nERRO: Aceder a memória não alocada em " << __PRETTY_FUNCTION__ << "\n"  << endl;
      return Vec();
    }

  const int N = Get_nRows();

  double *ColArray = new double[N];

  for (int k = 0; k < N; ++k)
    ColArray[k] = M[k][j];

  Vec Col(N, ColArray);

  delete[] ColArray;

  return Col;
}

// Determinante
double FCmatrixFull::GetDeterminant() const
{
  const int N = Get_nCols();

  // Só se calcula o determinante para matrizes quadradas
  if (N != Get_nRows())
    {
      cout << "\nERRO: Operação inválida em " << __PRETTY_FUNCTION__ << "\n" << endl;
      return 0;
    }

  // Matriz 1x1
  else if (N == 1)
    return M[0][0];

  // Matriz 2x2
  else if (N == 2)
    return M[0][0] * M[1][1] - M[0][1] * M[1][0];

  // Matriz 3x3
  else if (N == 3)
    return M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] + M[0][2] * M[1][0] * M[2][1] - M[0][2] * M[1][1] * M[2][0] - M[1][2] * M[2][1] * M[0][0] - M[2][2] * M[0][1] * M[1][0];

  // Matriz maior (regra dos cofatores inicialmente)
  else
    {
      double determinante=1.;
      FCmatrixFull Matriz_Gauss = M;
      FCmatrixAlgorithms::GaussElimination (Matriz_Gauss, 0, 0); // Faço sem pivotagem
      for (int i=0; i<N; i++)
	determinante *= Matriz_Gauss[i][i];

      return determinante;
    }
}
  
// Valor máximo de linha, em módulo
int FCmatrixFull::GetRowMax(int i) const
{
  const int N = Get_nRows();

  if (i < 0 || i >= N)
    {
      throw invalid_argument(TString::Format("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
    }

  else
    {
      //const int M = Get_nCols();
      const Vec Row = GetRow(i);

      int CurrentMax = 0;

      for (int k = 0; k < N; k++)
	if (abs(Row[k]) > abs(Row[CurrentMax]))
	  CurrentMax = k;

      return CurrentMax;
    }
}

// Devolve o índice da linha que para a qual o quociente entre o valor na coluna j dessa linha e o valor máximo dessa linha seja máximo (tudo em módulo)
int FCmatrixFull::GetColMax(int i, int j) const
{
  const int n = Get_nRows();
  const int m = Get_nCols();

  // Valor indevido para j
  if (j < 0 || j >= m || i < 0 || i >= n)
    {
      throw invalid_argument(TString::Format("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
    }

  else
    {
      int CurrentMax = i; // Índice da linha (a partir da linha i) com o maior valor
      double CurrentMaxValue = 0.;
      double quociente; // Entre membro da coluna e maior valor absoluto da linha (tudo em módulos)
      int indice_max_linha; // Índice do maior valor da linha em módulo

      // Percorrer as linhas
      for (int k = i; k < n; k++)
	{
	  indice_max_linha = GetRowMax (k);

	  //if (abs(M[k][indice_max_linha]) > TOLERANCE)
	  quociente = abs(M[k][j]) / abs(M[k][indice_max_linha]);

	  if (quociente > CurrentMaxValue)
	    {
	      CurrentMaxValue = quociente;
	      CurrentMax = k;
	    }
	  
	  // Se se encontrou um elemento com relative size 1 (o máximo possível), não é preciso continuar
	  if (CurrentMaxValue == 1.)
	    break;
	}

      return CurrentMax;
    }
}

// Trocar 2 linhas
void FCmatrixFull::swapRows(int i, int j)
{
  const int N = Get_nRows();

  if (i < 0 || j < 0 || i >= N || j >= N)
    cout << "\nERRO: Aceder a memória não alocada em " << __PRETTY_FUNCTION__ << "\n"  << endl;

  else if (i != j)
    {
      Vec vetor_troca(M[i]);
      M[i] = M[j];
      M[j] = vetor_troca;
    }
}

// cout <<
ostream& operator<< (ostream& s, const FCmatrixFull& matrix) {
  s << "        [\n";
  for (int i=0; i<matrix.Get_nRows(); ++i) {
    s << "           " << matrix.M[i] << "\n";
  }
  s << "        ]\n";
  return s;
}

// Get Lower Diagonal
Vec FCmatrixFull::Get_LowDiag() const
{
  int n_max;

  // Verificar se há mais linhas ou colunas
  if (Get_nRows() >= Get_nCols())
    n_max = Get_nRows();
  else
    n_max = Get_nCols();

  int n1 = n_max - 1;

  double *low_diag = new double[n1];

  // Armazenar os valores da diagonal inferior
  for (int i = 0; i < n1; ++i)
    low_diag[i] = M[i + 1][i];

  Vec LowDiag (n1, low_diag);
  
  delete[] low_diag;

  return LowDiag;
}

// Get Middle Diagonal
Vec FCmatrixFull::Get_MidDiag() const
{
  int n_max;

  if (Get_nRows() >= Get_nCols())
    n_max = Get_nRows();
  else
    n_max = Get_nCols();
  
  double *mid_diag = new double[n_max];

  for (int i = 0; i < n_max; ++i)
    mid_diag[i] = M[i][i];

  Vec MidDiag (n_max, mid_diag);

  delete[] mid_diag;

  return MidDiag;
}

// Get Upper Diagonal
Vec FCmatrixFull::Get_UppDiag() const
{
  int n_max;

  if (Get_nRows() >= Get_nCols())
    n_max = Get_nRows();
  else
    n_max = Get_nCols();

  int n1 = n_max - 1;

  double *up_diag = new double[n1];

  for (int i = 0; i < n1; ++i)
    up_diag[i] = M[i][i + 1];

  Vec UppDiag(n1, up_diag);

  delete[] up_diag;

  return UppDiag;
}


// Adds a column to the matrix
void FCmatrixFull::Augment (const Vec& vetor) {

  int nrows = Get_nRows();
  
  if (vetor.size() != nrows)
    throw invalid_argument(TString::Format("[%s] vector has more elements than the matrix's number of lines!\n", __PRETTY_FUNCTION__));
    
  for(int i = 0; i < nrows; i++) {
    M[i].AddEntry(vetor[i]);
  }
}

Vec FCmatrixFull::RemoveLastCol() {

  int nrows = Get_nRows();
  double array[nrows];
  
  for (int i = 0; i < nrows; i++) {

    array[i] = M[i].RemoveLastEntry();

  }

  return Vec(nrows, array);
}


double FCmatrixFull::GetSumLine(int i) const
{
  const int n = Get_nRows();
  const int m = Get_nCols();
  
  double sum = 0.;      

  if (i < 0 || i >= n)
    {
      cout << "\nERRO: Aceder a memória não alocada em " << __PRETTY_FUNCTION__ << "\n"  << endl;
      return sum;
    }
  else
    {
      for (int j=0; j<m; j++)
	sum += abs(M[i][j]);
      return sum;
    }
}


double FCmatrixFull::GetNormaInfMatriz() const
{
  const int n = Get_nRows();
  double sum;
  double max = 0.;

  for (int i=0; i<n; i++)
    {
      sum = GetSumLine (i);
      if (sum > max)
	max = sum;
    }

  return max;
}

double FCmatrixFull::GetNorma2Matriz() const
{
  const int n = Get_nRows();
  const int m = Get_nCols();
  double sum = 0.;

  for (int i=0; i<n; i++)
    {
      for (int j=0; j<m; j++)
	sum += M[i][j]*M[i][j];
    }

  sum = sqrt (sum);
  return sum;
}

bool FCmatrixFull::IsDiagonallyDominant() const {
  bool resultado = true;
  const int n = Get_nRows();
  for (int i=0; i<n; i++) {
    if (abs(M[i][i]) <= GetSumLine(i) - abs(M[i][i]))
      resultado = false;
  }
  return resultado;
}
