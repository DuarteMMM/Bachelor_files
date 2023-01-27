#include "Vandermonde.h"
#include "FCmatrixFull.h"
#include "FCmatrix.h"
#include "Vec.h"
#include "EqSolver.h"
#include "FCmatrixAlgorithms.h"

#include <vector> // push_back
#include <iostream>
#include <stdexcept> // std::invalid_argument
#include <algorithm> //max
#include <cstdlib> //abs

#include "TGraph.h"
#include "TAxis.h"
#include "TF1.h"
#include "TString.h" // Format
#include "TMath.h"

//#define DEBUG
#define PIVOTAGEM 1 //0 - gauss sem pivotagem, 1 - gauss com pivotagem

using namespace std;


///////////////////////constructors and destructors


Vandermonde::Vandermonde() :
  n(0),
  x(nullptr),
  y(nullptr),
  fPoly(nullptr) {;}
  

  
Vandermonde::Vandermonde(unsigned ext_n, double ext_x, double ext_y, const TF1& underlying_func) {

  
  if (ext_n >= 0) {

    n = ext_n;
    x = new double[n];
    y = new double[n];
    
    if (ext_x != ext_y) {

      //inicialização dos vetores de pontos
      
      double max = std::max(ext_x, ext_y);
      double min = std::min(ext_x,ext_y);
      double step = (max-min)/(n-1);
      int nminus1 = n-1;
      
      x[0] = min;
      y[0] = underlying_func.Eval(x[0]);

      for (int i = 1; i < nminus1; i++) {

	x[i] = x[i-1] + step;
	y[i] = underlying_func.Eval(x[i]);
      }

      x[nminus1] = max;
      y[nminus1] = underlying_func.Eval(x[nminus1]);
      
      //criação da matriz de coeficientes
      
      double** c_matrix = new double* [n];

      for (int i = 0; i < n; i++) {

	c_matrix[i] = new double[n];
	c_matrix[i][0] = 1.;
	
	for (int j = 1; j < n; j++) {

	  c_matrix[i][j] = c_matrix[i][j-1] * x[i];
	  
	}

      }

#ifdef DEBUG
      //cout << "antes da criação da matriz" << endl;
#endif

      FCmatrixFull* matriz = new FCmatrixFull(c_matrix, n, n);
      MatrixCoefs = *matriz;
      delete matriz;

#ifdef DEBUG
      //cout << "depois da criação da matriz" << endl;
#endif
      
      for (int i = 0; i < n; i++) {
	delete[] c_matrix[i];
      }
      delete[] c_matrix;

      
      //cálculo dos coeficientes polinomiais

      Vec coefs_y (n, y);
      
      EqSolver solve_for_polcoefs (MatrixCoefs, coefs_y);

#ifdef DEBUG
      //solve_for_polcoefs.ShowMatrix();
#endif
      
      PolCoefs = solve_for_polcoefs.GaussEliminationSolver(PIVOTAGEM); //1 - com pivotagem, 0 - sem pivotagem

#ifdef DEBUG
      //cout << "depois de determinar coeficientes" << endl;
      //cout << "coefs_y: " << coefs_y << endl;
#endif


      SetGraphicsPoints();
      SetPolynomialFunction();
      
    } else {

      throw invalid_argument(TString::Format("[%s] received equal interval extremes...!\n", __PRETTY_FUNCTION__));

    }
   
  } else {

    throw invalid_argument(TString::Format("[%s] received invalid number of points...!\n", __PRETTY_FUNCTION__));

  }


}


Vandermonde::~Vandermonde() {
  delete fPoly;
  delete [] x;
  delete [] y;
}


/////////////////////////////////////////setters


void Vandermonde::SetGraphicsPoints() {

  gPoints.Set(n); //set number of points
  double xmin = x[0];
  double xmax = x[n-1];
  auto pair = minmax_element(y, y+n);
  double ymin = *(pair.first);
  double ymax = *(pair.second);
  
  for(int i = 0; i < n; i++) {

    gPoints.SetPointX(i, x[i]);
    gPoints.SetPointY(i, y[i]);

  }

  //gPoints.SetName("gPoints");
  gPoints.SetMarkerStyle(20);
  gPoints.SetMarkerColor(38);
  gPoints.SetMarkerSize(2);

  //gPoints.GetXaxis()->SetRangeUser(xmin-0.1*abs(xmin), xmax+0.1*abs(xmax));
  gPoints.GetXaxis()->SetLimits(xmin-0.05,xmax+0.05);
  gPoints.GetXaxis()->SetTitle("x");
  //gPoints.GetYaxis()->SetRangeUser(ymin-0.1*abs(ymin), ymax+0.1*abs(ymax));
  gPoints.GetYaxis()->SetTitle("y");
  gPoints.SetTitle ("y(x) = sin(2#pix) + 0.002cos(100x)");

}


void Vandermonde::SetPolynomialFunction() {

  fPoly = new TF1("", [&](double* x, double* p){double result = PolCoefs[n-1];    for (int i = n-2; i >= 0; i--){result *= x[0]; result += PolCoefs[i];}return result;}, x[0], x[n-1], 2);
 

  fPoly->SetLineColor(kRed+2);
  fPoly->SetLineStyle(1);
  fPoly->SetLineWidth(2);
  fPoly->GetXaxis()->SetTitle("X axis");
  fPoly->GetYaxis()->SetTitle("Y axis");
  //fPoly->GetXaxis()->SetRangeUser(x[0]-0.1*abs(x[0]), x[n-1]+0.1*abs(x[n-1]));
}



//////////////////////////getters


TGraph& Vandermonde::GetGraphPoints() {

  return gPoints;

}


TF1& Vandermonde::GetPolyFunc() {

  return *fPoly;

}


const FCmatrixFull& Vandermonde::GetMatrix() {

  return MatrixCoefs;
  
}


const Vec& Vandermonde::GetCoefficients() {

  return PolCoefs;

}


const double* Vandermonde::GetX() {

  return x;

}


const double* Vandermonde::GetY() {

  return y;

}


///////////////////////////Matrix_Invertor


void Vandermonde::GetInverseMatrix(FCmatrixFull& matriz)
{
  // Criar matriz identidade
  n = matriz.Get_nRows();
  if (n != matriz.Get_nCols())
    throw invalid_argument(TString::Format("[%s] received a non-square matrix!\n", __PRETTY_FUNCTION__));

  vector<Vec> vetores;
  Vec v (n);
  v[0] = 1.;
  vetores.push_back (v);
  
  for (int i=1; i<n; i++)
    {
      v[i-1] = 0.;
      v[i] = 1.;
      vetores.push_back (v);
    }

  FCmatrixFull I(vetores); // Matriz identidade

  // Multiplicar as duas matrizes pelo fator 100., para evitar produtos e multiplicações entre números muito pequenos
  I=I*100.;
  matriz=matriz*100.;
  FCmatrixAlgorithms::GaussJordan (matriz, I, 1);
  matriz = I;
}


/////////////////////////////////////Errors


double Vandermonde::GetCoeffError() {

  Vec b (n, y);

#ifdef DEBUG
  //cout << "b: " << b << endl;
#endif 
  
  Vec d = MatrixCoefs*PolCoefs-b;

#ifdef DEBUG
  //cout << "C:" << MatrixCoefs << endl;
  cout << "a:" << PolCoefs << endl;
  cout << "n-1: " << n-1 << endl << MatrixCoefs[n-1][n-1] << endl; 
  //cout << "C*a: " << MatrixCoefs*PolCoefs << endl;
  //cout << "d: " << d << endl;
#endif
  
  return abs(d.maxAbs());
}
