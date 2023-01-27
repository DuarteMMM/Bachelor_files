#ifndef __NEWTONINTERPOLATOR__
#define __NEWTONINTERPOLATOR__


#include "DataPoints.h"

#include "TGraph.h"
#include "TCanvas.h"

#include <string>


class NewtonInterpolator : public DataPoints {

  
public:

  //default constructors and destructors
  NewtonInterpolator(unsigned int N_ext= 0, const double* x_ext = NULL, const double* y_ext = NULL, const TF1* fF0 = NULL);
  ~NewtonInterpolator();

  //copyconstructor
  NewtonInterpolator(const NewtonInterpolator&);

  
  //interpolation
  double Interpolate (double) const;

  
  //graphics
  void Draw();
  void SetResolution (int n=200) const;
  
  
  //getters
  const TF1& GetInterpolationFunction();
  const TF1& GetUnderlyingFunction();
  TCanvas* GetCanvas();


  //setters
  void SetUnderlyingFunction (const TF1*);


  //friends
  friend ostream& operator<< (ostream&, const NewtonInterpolator&); 
  

private:
  
  double functor(double* fx, double* par) {
    return Interpolate(fx[0]);
  }
  
  TF1* f_interp; // interpolating function
  TF1* f_under; //underlying function
  TCanvas* canvas;


};


#endif
