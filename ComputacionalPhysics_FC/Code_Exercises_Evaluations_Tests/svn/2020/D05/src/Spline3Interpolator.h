#ifndef __Spline3Interpolator__
#define __Spline3Interpolator__

#include "Vec.h"
#include "DataPoints.h"
#include "TF1.h"
#include "TCanvas.h"

class Spline3Interpolator : public DataPoints {

public:

  // constructors and destructors
 Spline3Interpolator (int N=0, double *x=NULL, double *y=NULL);

 Spline3Interpolator (const Spline3Interpolator&);

 ~Spline3Interpolator();
 
 // interpolation and derivatives
 double Interpolate (double) const;
 double InterpolateFirstDerivative (double) const;
 double InterpolateSecondDerivative (double) const;
 
 // getters
 TF1* GetFInterpolator() {return FInterpolator;}
 TCanvas* GetCanvas();
 
 TF1* GetFInterpolatorFirstDerivative() {return FInterpolatorFirstDerivative;}

 TF1* GetFInterpolatorSecondDerivative() {return FInterpolatorSecondDerivative;}

 // graphics
 void Draw();
 void SetResolution (int n=200) const;
 
 // friends
  friend ostream& operator<< (ostream&, const Spline3Interpolator&); 
 
private:

 void SetCurvatureLines ();
 
 double fInterpolator (double *fx, double *par) {
  return Interpolate (fx[0]);
  }
  
 double fInterpolatorFirstDerivative (double *fx, double *par) {
  return InterpolateFirstDerivative (fx[0]);
  }
  
 double fInterpolatorSecondDerivative (double *fx, double *par) {
  return InterpolateSecondDerivative (fx[0]);
  }
  
 TF1* FInterpolator;
 TF1* FInterpolatorFirstDerivative;
 TF1* FInterpolatorSecondDerivative;
 TCanvas* canvas;
 double* K; // 2nd derivatives
};

#endif
