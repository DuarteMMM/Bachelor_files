#ifndef __INTEGRATOR__
#define __INTEGRATOR__

#include "Func1D.h"
#include "Derivator.h"

#include <iostream>

#include "TF1.h"


using namespace std;


class Integrator : public Func1D {

 public:

  // constructors and destructors
  Integrator(); 
  Integrator(TF1*, double, double); // function, min, max
  Integrator(const Integrator&);
  ~Integrator() = default;
  
  // Integration methods
  void Trapezoidal(int, double&, double&);
  void TrapezoidalAdaptative (int, double&, double&);

  void Simpson(int, double&, double&); //n must be even

  void Romberg(int&, int&, double&, double&);//j - accuracy, n - number of steps (n>=j)

  // Operators
  Integrator operator+();
  Integrator operator-();

  // Other methods
  double GetXMin() const;
  double GetXMax() const;
  void SetXMin(double);
  void SetXMax(double);
  
  // Friends
  friend ostream& operator<< (ostream&, const Integrator&);
  

 private:
  
  double xmin, xmax;
};


#endif
