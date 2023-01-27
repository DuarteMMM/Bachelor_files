#include <cmath>

#include "RootFinder.h"

#include "TF1.h"


#define TOLERANCE 1e-10


///////////////////////////7constructors and destructors
RootFinder::RootFinder() : Func1D(), xmin(0.), xmax(0.) {}


RootFinder::RootFinder(const TF1* func, double min, double max): Func1D(func), xmin(min), xmax(max) {}


RootFinder::RootFinder(const TF1& func, double min, double max): Func1D(func), xmin(min), xmax(max) {}


RootFinder::RootFinder(const Func1D& func, double min, double max): Func1D(func), xmin(min), xmax(max) {}


RootFinder::RootFinder(const RootFinder& r): RootFinder(r.f, r.xmin, r.xmax) {}


///////////////////////////////root-finding methods


double RootFinder::SecantMethod(double i0, double iminus1, double& error, int repeats) {

  double curr_it = i0;
  double prev_it = iminus1;
  double next_it = 0.;

  double expected_error = error;
  
  for(int i = 0; i < repeats; i++) {

    double eval_curr = this->Eval(curr_it);

    if (fabs(eval_curr) < TOLERANCE) {
      break;
    }
      
    next_it = curr_it - eval_curr*(curr_it-prev_it)/(eval_curr - this->Eval(prev_it));

    if(fabs(curr_it-prev_it) < error) {

      break;

    }
    
    prev_it = curr_it;
    curr_it = next_it;
    
  }

  error = curr_it-prev_it;
  return curr_it;
}


///////////////////////////////////getters


double RootFinder::getXMin() {

  return xmin;

}


double RootFinder::getXMax() {

  return xmax;

}


///////////////////////////////////setters


void RootFinder::setXMin (double min) {

  xmin = min;

}


void RootFinder::setXMax(double max) {

  xmax = max;

}
