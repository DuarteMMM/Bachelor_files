#include "EqSolver.h"
#include "Spline3Interpolator.h"

#include "TCanvas.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TAxis.h"

#include <cstdio>
#include <string>

#include "Vec.h"
#include "FCmatrixFull.h"

#include <iostream>

using namespace std;

Spline3Interpolator::Spline3Interpolator(int fN, double *fx, double *fy) : DataPoints(fN,fx,fy) {
  
  FInterpolator = new TF1("FInterpolator", this, &Spline3Interpolator::fInterpolator, xmin, xmax, 0);
  
  FInterpolatorFirstDerivative = new TF1("FInterpolatorFirstDerivative", this, &Spline3Interpolator::fInterpolatorFirstDerivative, xmin, xmax, 0);
  FInterpolatorSecondDerivative = new TF1("FInterpolatorSecondDerivative", this, &Spline3Interpolator::fInterpolatorSecondDerivative, xmin, xmax, 0);
  
  K = new double[N];
  SetCurvatureLines(); // define segment interpolators
  
}

//copy constructor
Spline3Interpolator::Spline3Interpolator(const Spline3Interpolator& I) : Spline3Interpolator(I.N, I.x, I.y) {;}

Spline3Interpolator::~Spline3Interpolator() {
  if (FInterpolator) delete FInterpolator;
  if (FInterpolatorFirstDerivative) delete FInterpolatorFirstDerivative;
  if (FInterpolatorSecondDerivative) delete FInterpolatorSecondDerivative;

  // Há situações em que o programa não executa com os deletes abaixo...
  //if (canvas) delete canvas;
  //if (K) delete K;
}


TCanvas* Spline3Interpolator::GetCanvas() {

  if (canvas) delete canvas;
  canvas = new TCanvas("cInterpolator", "", 0, 0, 1000, 800);
  Draw();
  canvas->Modified();
  
  return canvas;
}


void Spline3Interpolator::SetCurvatureLines() {
  double **TriMatrixArray = new double* [N-2];
  double *ArrayConstants = new double[N-2];
  
  for (int i=0; i<N-2; i++){
    TriMatrixArray[i] = new double[N-2];
    for (int j=0; j<i-1; j++)
      TriMatrixArray[i][j] = 0.;
    if (i>0)
      TriMatrixArray[i][i-1] = x[i]-x[i+1];
    TriMatrixArray[i][i] = 2*(x[i]-x[i+2]);
    if (i<N-3)
      TriMatrixArray[i][i+1] = x[i+1]-x[i+2];

    i++;
    ArrayConstants[i-1] = 6* ( (y[i-1]-y[i+1]) / (x[i-1]-x[i]) - (y[i]-y[i+1]) / (x[i]-x[i+1]) );
    i--;
  }
  
  FCmatrixFull TriMatrix(TriMatrixArray, N-2, N-2);
  Vec Constants(N-2, ArrayConstants);

  EqSolver System (TriMatrix, Constants);
  Vec VecK = System.GaussEliminationSolver(1);
  K = VecK.GetEntries();

  // Apagar os arrays da memória
  for (int k=0; k<N-2; k++)
    delete TriMatrixArray[k];
  delete [] TriMatrixArray;

  delete ArrayConstants;
}

double Spline3Interpolator::Interpolate (double fx) const {
  
  int j; // Nos slides, usado i ou j...
  
  //detect in which segment is x
  for (j=0; j<=N; j++) {
    if ((fx-x[j])<0.) break;
  }

  // Com 6 pontos, por exemplo:
  // Se está atrás de x0: j=0
  // Entre x0 e x1: j=1
  // Entre x1 e x2: j=2
  // Entre x2 e x3: j=3
  // Entre x3 e x4: j=4
  // Entre x4 e x5: j=5
  // Após x5: j=6
  
  if (j==0 || j==N)
    throw invalid_argument (TString::Format("[%s]: point received is out of range.\n", __PRETTY_FUNCTION__));

  else
    j--;

  double value;

  // Não existe o K_i dos slides
  if (j==0)
    value = - (K[j]/6) * ( pow( (fx-x[j]), 3) / (x[j]-x[j+1]) - (fx-x[j]) * (x[j]-x[j+1]) ) + ( y[j] * (fx-x[j+1]) - y[j+1] * (fx-x[j]) ) / ( x[j]-x[j+1] );

  // Não existe o K_i+1 dos slides
  if (j==N-2)
    value = (K[j-1]/6) * ( pow( (fx-x[j+1]), 3) / (x[j]-x[j+1]) - (fx-x[j+1]) * (x[j]-x[j+1])) + ( y[j] * (fx-x[j+1]) - y[j+1] * (fx-x[j]) ) / ( x[j]-x[j+1] );

  else
    value = (K[j-1]/6) * ( pow( (fx-x[j+1]), 3) / (x[j]-x[j+1]) - (fx-x[j+1]) * (x[j]-x[j+1]))  - (K[j]/6) * ( pow( (fx-x[j]), 3) / (x[j]-x[j+1]) - (fx-x[j]) * (x[j]-x[j+1]) ) + ( y[j] * (fx-x[j+1]) - y[j+1] * (fx-x[j]) ) / ( x[j]-x[j+1] );

  return value;
}



double Spline3Interpolator::InterpolateFirstDerivative (double fx) const {
  
  int j;
  
  for (j=0; j<=N; j++) {
    if ((fx-x[j])<0.) break;
  }
  
  if (j==0 || j==N)
    throw invalid_argument (TString::Format("[%s]: point received is out of range.\n", __PRETTY_FUNCTION__));

  else
    j--;

  double value;

  if (j==0)
    value = -(K[j]/6.) * ( ( 3. * (fx-x[j])*(fx-x[j]) ) / (x[j]-x[j+1]) - (x[j]-x[j+1]) ) + (y[j]-y[j+1]) / (x[j]-x[j+1]);

  if (j==N-2)
    value = (K[j-1]/6.) * ( ( 3. * (fx-x[j+1])*(fx-x[j+1]) ) / (x[j]-x[j+1]) - x[j]-x[j+1]) + (y[j]-y[j+1]) / (x[j]-x[j+1]);

  else
    value = (K[j-1]/6.) * ( ( 3. * (fx-x[j+1])*(fx-x[j+1]) ) / (x[j]-x[j+1]) - x[j]-x[j+1]) -(K[j]/6.) * ( ( 3. * (fx-x[j])*(fx-x[j]) ) / (x[j]-x[j+1]) - (x[j]-x[j+1]) ) + (y[j]-y[j+1]) / (x[j]-x[j+1]);

  return value;
}

double Spline3Interpolator::InterpolateSecondDerivative (double fx) const {
  
  int j;
  
  for (j=0; j<=N; j++) {
    if ((fx-x[j])<0.) break;
  }

  
  if (j==0 || j==N)
    throw invalid_argument (TString::Format("[%s]: point received is out of range.\n", __PRETTY_FUNCTION__));

  else
    j--;

  double value;

  if (j==0)
    value = -K[j] * ( (fx-x[j]) / (x[j]-x[j+1]) );

  if (j==N-2)
    value = K[j-1] * ( (fx-x[j+1]) / (x[j]-x[j+1]) );

  else
    value = K[j-1] * ( (fx-x[j+1]) / (x[j]-x[j+1]) ) - K[j] * ( (fx-x[j]) / (x[j]-x[j+1]) );

  return value;
}



void Spline3Interpolator::Draw() {
  
  DataPoints::Draw();
  FInterpolator->SetLineColor(1);
  FInterpolator->SetLineWidth(2);
  FInterpolator->Draw("same");
  gPoints->SetTitle("Cubic Spline interpolating function");
  
  double minimum_y = FInterpolator->GetMinimum();
  double maximum_y = FInterpolator->GetMaximum();
  gPoints->GetYaxis()->SetRangeUser (minimum_y - 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.), maximum_y + 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.) );
  
}

void Spline3Interpolator::SetResolution (int n) const {
  FInterpolator->SetNpx(n);
}

ostream& operator<< (ostream& s, const Spline3Interpolator& I) {

  s << "Spline 3 Interpolator " << "x: [" << I.xmin << ", " << I.xmax << "]" << endl;

  for(int i = 0; i < I.N; i++) {

    s << fixed << setprecision(3) << "(" << I.x[i] << ", " << I.y[i] << ") f(x)=" << I.Interpolate(I.x[i]) << ";";

  }
  s << endl;

  return s;
}

