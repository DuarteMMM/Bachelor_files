#include "OpticalMat.h"
#include <iostream>


using namespace std;



void OpticalMat::SetRefIndex (vector<pair<float, float> > v) {
  RefIndex = v;
}


vector<pair<float, float> > OpticalMat::GetRefIndex () {return RefIndex;}


void OpticalMat::SetFitRefIndex (TF1* function) {
  f = function;
}


TF1* OpticalMat::GetFitRefIndex () {return f;}


/*void OpticalMat::DrawRefIndexPoints() {



}



void OpticalMat::DrawFitRefIndex() {



}


double FitRefIndex(double* x, double* par) {

  return par[0] + par[
  
  }*/
