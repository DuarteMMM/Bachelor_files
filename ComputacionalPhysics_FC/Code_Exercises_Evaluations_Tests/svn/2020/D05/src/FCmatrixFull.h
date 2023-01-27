#ifndef __FCmatrixFull__
#define __FCmatrixFull__

#include "FCmatrix.h"
#include "Vec.h"
#include <iostream>

using namespace std;

class FCmatrixFull : public FCmatrix
{
public:
  //Constructors
  FCmatrixFull();
  FCmatrixFull(double **, int, int); //matrix, rows, columns
  FCmatrixFull(double *, int, int); //all elements in array, rows, columns
  FCmatrixFull(vector<Vec>);

  FCmatrixFull(const FCmatrixFull&); // Copy constructor

  
  // Operators
  Vec& operator[](int); // Return the row with a given index (starting at 0)
  FCmatrixFull operator=(const FCmatrix &); // Equal a Fullmatrix to any matrix
  FCmatrixFull operator+(const FCmatrix &) const; // Add a matrix to a Fullmatrix
  FCmatrixFull operator-(const FCmatrix &) const; // Subtract a matrix from a Fullmatrix
  FCmatrixFull operator*(const FCmatrix &) const; // Multiply a Fullmatrix and a matrix
  FCmatrixFull operator*(double) const; // Multiply Fullmatrix by scalar
  Vec operator*(const Vec&) const; // Multiply Fullmatrix by Vec

  
  // Getters
  int Get_nRows() const; // Return the number of rows in a Fullmatrix
  int Get_nCols() const; //Return the number of collumns in a Fullmatrix

  Vec GetRow(int i) const; // Retrieve row of index i
  Vec GetCol(int j) const; // Retrieve column of index j
  
  double GetDeterminant() const; //Return a Fullmatrix's determinant
    
  int GetRowMax (int i = 0) const; // Retornar índice (coluna) do membro da linha com maior valor absoluto
  int GetColMax (int i = 0, int j = 0) const; // Retornar o índice da linha >=i com o maior valor do quociente valor absoluto/maior valor absoluto da respetiva linha para a coluna j

  Vec Get_LowDiag() const; // Return the lower diagonal
  Vec Get_MidDiag() const; // Return the middle diagonal
  Vec Get_UppDiag() const; // Return the upper diagonal

  
  //Other Methods
  void swapRows(int, int); // Trocar linhas com índices dados
  void Augment(const Vec&);

  Vec RemoveLastCol(); //removes the last column
  //void Print() const; // Print da Fullmatrix

  double GetSumLine(int i = 0) const; // Retornar soma dos módulos dos elementos da linha
  double GetNormaInfMatriz() const; // Norma infinito da matriz
  double GetNorma2Matriz() const; // Norma 2 da matriz
  
  bool IsDiagonallyDominant() const; // Verifica se a matriz é diagonally dominant
  

  //friends
  friend   ostream& operator<< (ostream& , const FCmatrixFull& ); // Escrever matriz com precisão 6
  //friend operator*

};

#endif
