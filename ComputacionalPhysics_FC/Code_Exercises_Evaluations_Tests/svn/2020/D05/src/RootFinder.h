#ifndef __ROOTFINDER__
#define __ROOTFINDER__

#include "Func1D.h"

#include "TF1.h"


class RootFinder : public Func1D {
  
 public:

  //constructors and destructors
  RootFinder();
  RootFinder(const TF1*, double, double);
  RootFinder(const TF1&, double, double);
  RootFinder(const RootFinder&);
  RootFinder(const Func1D&, double, double);
  ~RootFinder() = default;
  
  //root-finding methods
  double SecantMethod(double i0, double iminus1, double& error, int repeats);

  //setters

  void setXMin(double);
  void setXMax(double);

  //getters

  double getXMin();
  double getXMax();
  
  
 protected:

    double xmin, xmax;

};

#endif
