#include "NevilleInterpolator.h"

#include "TF1.h"
#include "TGraph.h"
#include "TAxis.h"

#include <string>
#include <algorithm> //min_element max_element


#define DEBUG


using namespace std;


//constructors and destructor
NevilleInterpolator::NevilleInterpolator(unsigned int N_ext, const double* x_ext, const double* y_ext, const TF1* fF0) :
  DataPoints::DataPoints(N_ext, x_ext, y_ext),
  f_under(nullptr),
  canvas (nullptr){

  if (fF0) f_under = new TF1(*fF0);
  f_interp = new TF1("FInterpolator", this, &NevilleInterpolator::functor, xmin, xmax, 0); //nome, classe a que pertence o functor, ref p/ functor, min do intervalo, max do intervalo, args do functor

}


NevilleInterpolator::~NevilleInterpolator() {

  if (f_interp) delete f_interp;
#ifdef DEBUG
  cout << "deleted f_interp" << endl;
#endif
  
  if (f_under) delete f_under;
#ifdef DEBUG
  cout << "deleted f_under" << endl;
#endif
  
  if (canvas) delete canvas;
#ifdef DEBUG
  cout << "deleted canvas" << endl;
#endif
}


//copy constructor
NevilleInterpolator::NevilleInterpolator(const NevilleInterpolator& Nev) : NevilleInterpolator(Nev.N, Nev.x, Nev.y, Nev.f_under) {;}


//////////////////////////////////////////getters


const TF1& NevilleInterpolator::GetInterpolationFunction() {

  return *f_interp;

}


const TF1& NevilleInterpolator::GetUnderlyingFunction() {

  return *f_under;

}


TCanvas* NevilleInterpolator::GetCanvas() {

  if (canvas) delete canvas;
  canvas = new TCanvas("cInterpolator", "", 0, 0, 1000, 800);
  Draw();
  canvas->Modified();
  
  return canvas;
}


/////////////////////////////////////Setters


void NevilleInterpolator::SetUnderlyingFunction (const TF1* fF0) {

  if (fF0) {
    
    delete f_under;
    
    f_under = new TF1 (*fF0);

  }

}


////////////////////////////////////Interpolation


double NevilleInterpolator::Interpolate (double input) const {

  double polynomials[N];

  copy(y, y+N, polynomials);

  //order é a ordem do polinómio
  for (int order = 1; order < N; order++) {

    //n é o índice do ponto
    for (int n = 0; n < (N - order); n++) {
      
      int orderplusn = order + n;
      double intervalwidth = x[n] - x[orderplusn];
      polynomials[n] = polynomials[n]*(input - x[orderplusn])/intervalwidth;
      polynomials[n] -= polynomials[n+1] * (input - x[n])/intervalwidth;
      
    }
  }

  return polynomials[0];
}


////////////////////////////graphics


void NevilleInterpolator::Draw() {

  DataPoints::Draw();
  f_interp->SetLineColor(1);
  f_interp->SetLineWidth(2);
  f_interp->Draw("same");
  gPoints->SetTitle("Neville interpolating function");
  
  double minimum_y = f_interp->GetMinimum();
  double maximum_y = f_interp->GetMaximum();
  gPoints->GetYaxis()->SetRangeUser (minimum_y - 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.), maximum_y + 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.) );

}


void NevilleInterpolator::SetResolution (int n) const {

  f_interp->SetNpx(n);

}


ostream& operator<< (ostream& s, const NevilleInterpolator& Nev) {

  s << "Neville Interpolator " << "x: [" << Nev.xmin << ", " << Nev.xmax << "]" << endl;

  for(int i = 0; i < Nev.N; i++) {

    s << fixed << setprecision(3) << "(" << Nev.x[i] << ", " << Nev.y[i] << ") f(x)=" << Nev.Interpolate(Nev.x[i]) << ";";

  }
  s << endl;

  return s;
}

