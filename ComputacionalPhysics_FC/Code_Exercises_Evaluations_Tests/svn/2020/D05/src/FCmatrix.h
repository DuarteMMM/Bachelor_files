#ifndef __FCmatrix__
#define __FCmatrix__

#include "Vec.h"
#include <vector>
#include <string>

using namespace std;

class FCmatrix {
  
protected:
  vector<Vec> M;    // Matrix entries
  string classname; // Type of matrix

  //friend class MatrixAlgs;
  
public:
  //Constructors
  FCmatrix();
  FCmatrix(double **arrays, int m, int n);
  FCmatrix(double *array, int m, int n);
  FCmatrix(const vector<Vec>&);
  FCmatrix(const FCmatrix&);
  
  //Operators
  virtual Vec &operator[](int) = 0;
  
  //Other Methods
  virtual double GetDeterminant() const = 0;

  //virtual Vec operator*(const Vec&) const; // Multiply Fullmatrix by Vec

  virtual int Get_nRows() const = 0;
  virtual int Get_nCols() const = 0;

  virtual Vec GetRow(int i) const = 0;
  virtual Vec GetCol(int i) const = 0;
  
  // Métodos para obter as diagonais; é útil nas Banded, por exemplo
  virtual Vec Get_LowDiag() const = 0;
  virtual Vec Get_MidDiag() const = 0;
  virtual Vec Get_UppDiag() const = 0;

  virtual int GetColMax(int i=0, int j = 0) const = 0;
  virtual int GetRowMax(int i = 0) const = 0;

  virtual double GetSumLine(int i = 0) const = 0;
  virtual double GetNormaInfMatriz() const = 0;
  virtual double GetNorma2Matriz() const  = 0;
  
  //virtual void swapRows(int, int); // Trocar linhas com índices dados
  //virtual void Augment(const Vec&);
  //virtual Vec RemoveLastCol(); 
  
  //Friends
  friend ostream& operator<< (ostream&, const FCmatrix&);
};

#endif
