#include "LagrangeInterpolator.h"

#include "TF1.h"
#include "TGraph.h"
#include "TAxis.h"

#include <string>
#include <algorithm> //min_element max_element
#include <iostream>


#define DEBUG


using namespace std;


//constructors and destructor
LagrangeInterpolator::LagrangeInterpolator(unsigned int N_ext, const double* x_ext, const double* y_ext, const TF1* fF0) :
  DataPoints::DataPoints(N_ext, x_ext, y_ext),
  f_under(nullptr),
  canvas (nullptr){

  if (fF0) f_under = new TF1(*fF0);
  f_interp = new TF1("FInterpolator", this, &LagrangeInterpolator::functor, xmin, xmax, 0); //nome, classe a que pertence o functor, ref p/ functor, min do intervalo, max do intervalo, args do functor

}


LagrangeInterpolator::~LagrangeInterpolator() {

  if (f_interp){ delete f_interp;
#ifdef DEBUG
  cout << "deleted f_interp" << endl;
#endif
  }
  
  if (f_under) {delete f_under;
#ifdef DEBUG
  cout << "deleted f_under" << endl;
#endif
  }
  if (canvas) {delete canvas;
#ifdef DEBUG
  cout << "deleted canvas" << endl;
#endif
  }

}


//copy constructor
LagrangeInterpolator::LagrangeInterpolator(const LagrangeInterpolator& L) : LagrangeInterpolator(L.N, L.x, L.y, L.f_under) {;}


//////////////////////////////////////////getters


const TF1& LagrangeInterpolator::GetInterpolationFunction() {

  return *f_interp;

}


const TF1& LagrangeInterpolator::GetUnderlyingFunction() {

  return *f_under;

}


TCanvas* LagrangeInterpolator::GetCanvas() {

  if (canvas) delete canvas;
  canvas = new TCanvas("cInterpolator", "", 0, 0, 1000, 800);
  Draw();
  canvas->Modified();
  
  return canvas;
}


/////////////////////////////////////Setters


void LagrangeInterpolator::SetUnderlyingFunction (const TF1* fF0) {

  if (fF0) {
    
    delete f_under;
    
    f_under = new TF1 (*fF0);

  }

}


////////////////////////////////////Interpolation
double LagrangeInterpolator::Interpolate(double input) const { 
    
  double result = 0;

  for (int i = 0; i < N; i++) {

    double term = y[i];

    for(int j = 0; j < N; j++) {
      if (j != i) {
	  
	term *= ((input - x[j]) / (x[i] - x[j]));

      }
    }
      
    result += term;
      
  }

#ifdef DEBUG
  if ((input < *min_element(x, x+N)) || (input > *max_element(x, x+N)))
    cout << "Interpolating outside of give interval.\n";
#endif
  
  return result;
}


////////////////////////////graphics


void LagrangeInterpolator::Draw() {

  DataPoints::Draw();
  f_interp->SetLineColor(1);
  f_interp->SetLineWidth(2);
  f_interp->Draw("same");
  gPoints->SetTitle("Lagrange interpolating function");
  
  double minimum_y = f_interp->GetMinimum();
  double maximum_y = f_interp->GetMaximum();
  gPoints->GetYaxis()->SetRangeUser (minimum_y - 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.), maximum_y + 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.) );

}


void LagrangeInterpolator::SetResolution (int n) const {

  f_interp->SetNpx(n);

}


ostream& operator<< (ostream& s, const LagrangeInterpolator& L) {

  s << "Lagrange Interpolator " << "x: [" << L.xmin << ", " << L.xmax << "]" << endl;

  for(int i = 0; i < L.N; i++) {

    s << fixed << setprecision(3) << "(" << L.x[i] << ", " << L.y[i] << ") f(x)=" << L.Interpolate(L.x[i]) << ";";

  }
  s << endl;

  return s;
}
