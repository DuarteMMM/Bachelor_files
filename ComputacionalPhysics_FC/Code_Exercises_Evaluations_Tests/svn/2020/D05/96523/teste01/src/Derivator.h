#ifndef __Derivator__
#define __Derivator__

#include "Func1D.h"

class Derivator : public Func1D{

public:
Derivator();
Derivator (TF1 *tf1 = NULL, double h1= 1.e-5); // Constructor
Derivator (const Derivator& d);
~Derivator() = default; // Destructor

// First Dertivative
Func1D Derivate1();
double FirstDerivative (double);

// Second Derivative
Func1D Derivate2();
double SecondDerivative (double);

// Third Derivati
Func1D Derivate3();
double ThirdDerivative (double);

// Second Derivative
Func1D Derivate4();
double FourthDerivative (double);

// Other methods
void SetH (double);
double GetH () const;


private:
double h; // Increment
double max, min; // Máximo e mínimo da função
};

#endif
