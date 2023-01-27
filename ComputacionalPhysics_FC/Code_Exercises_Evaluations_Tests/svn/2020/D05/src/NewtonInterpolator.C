#include "NewtonInterpolator.h"

#include "TF1.h"
#include "TGraph.h"
#include "TAxis.h"

#include <string>
#include <algorithm> // min_element max_element


#define DEBUG


using namespace std;


//constructors and destructor
NewtonInterpolator::NewtonInterpolator(unsigned int N_ext, const double* x_ext, const double* y_ext, const TF1* fF0) :
  DataPoints::DataPoints(N_ext, x_ext, y_ext),
  f_under(nullptr),
  canvas (nullptr){

  if (fF0) f_under = new TF1(*fF0);
  f_interp = new TF1("FInterpolator", this, &NewtonInterpolator::functor, xmin, xmax, 0); //nome, classe a que pertence o functor, ref p/ functor, min do intervalo, max do intervalo, args do functor

}


NewtonInterpolator::~NewtonInterpolator() {

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
NewtonInterpolator::NewtonInterpolator(const NewtonInterpolator& newton) : NewtonInterpolator(newton.N, newton.x, newton.y, newton.f_under) {;}


//////////////////////////////////////////getters


const TF1& NewtonInterpolator::GetInterpolationFunction() {

  return *f_interp;

}


const TF1& NewtonInterpolator::GetUnderlyingFunction() {

  return *f_under;

}


TCanvas* NewtonInterpolator::GetCanvas() {

  if (canvas) delete canvas;
  canvas = new TCanvas("cInterpolator", "", 0, 0, 1000, 800);
  Draw();
  canvas->Modified();
  
  return canvas;
}


/////////////////////////////////////Setters


void NewtonInterpolator::SetUnderlyingFunction (const TF1* fF0) {

  if (fF0) {
    
    delete f_under;
    
    f_under = new TF1 (*fF0);

  }

}


////////////////////////////////////Interpolation


double NewtonInterpolator::Interpolate (double input) const {

  double divided_differences[N];
  double result = 0;

  copy(y, y+N, divided_differences);

  //order é a ordem da diferença dividida
  for (int order = 1; order < N; order++) {

    //n é o índice do ponto
    for (int n = N-1; n >= order; n--) {
      
      int nminusorder = n - order;
      double intervalwidth = x[n] - x[nminusorder];
      divided_differences[n] = divided_differences[n]/intervalwidth;
      divided_differences[n] -= divided_differences[n-1]/intervalwidth;

    }
  }

  result = divided_differences[N-1];
  
  for(int i = (N-2); i >= 0; i--) {

    result *= (input - x[i]);
    result += divided_differences[i];

  }

  return result;
}


////////////////////////////graphics


void NewtonInterpolator::Draw() {

  DataPoints::Draw();
  f_interp->SetLineColor(1);
  f_interp->SetLineWidth(2);
  f_interp->Draw("same");
  gPoints->SetTitle("Newton interpolating function");
  
  double minimum_y = f_interp->GetMinimum();
  double maximum_y = f_interp->GetMaximum();
  gPoints->GetYaxis()->SetRangeUser (minimum_y - 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.), maximum_y + 0.1 * ( (abs(minimum_y) + abs(maximum_y) ) / 2.) );
  
}


void NewtonInterpolator::SetResolution (int n) const {

  f_interp->SetNpx(n);

}


ostream& operator<< (ostream& s, const NewtonInterpolator& newton) {

  s << "Newton Interpolator " << "x: [" << newton.xmin << ", " << newton.xmax << "]" << endl;

  for(int i = 0; i < newton.N; i++) {

    s << fixed << setprecision(3) << "(" << newton.x[i] << ", " << newton.y[i] << ") f(x) = " << newton.Interpolate(newton.x[i]) << ";";

  }
  s << endl;

  return s;
}


