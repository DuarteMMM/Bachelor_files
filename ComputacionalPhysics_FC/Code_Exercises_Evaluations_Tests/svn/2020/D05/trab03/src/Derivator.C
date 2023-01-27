/******************************************************
 *                Física Computacional                *
 *                    Derivator.C                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include "Derivator.h"
#include "TString.h" // TString::Format
#include <stdexcept> // throw::invalid_argument


using namespace std;


// Constructors
Derivator::Derivator() : Func1D(), h(0.), max(0.), min(0.) {;}

Derivator::Derivator(TF1 *tf1, double h1) : Func1D(tf1) {
  if (h1<=0.)
    throw invalid_argument(TString::Format("[%s] received a non positive h!\n", __PRETTY_FUNCTION__));
  h = h1;
  max = f->GetXmax();
  min = f->GetXmin();
}

Derivator::Derivator(const Derivator& d) : Func1D(d.f), h(d.h), max(d.max), min(d.min) {;}

// Primeira derivada em todo o domínio
Func1D Derivator::Derivate1() {
  auto f = [this](double *x, double *par=nullptr)
	   {
	     return FirstDerivative (x[0]);
	   };
  return Func1D(new TF1("First Derivative", f, min, max, 0));
}


// Primeira derivada em ponto x
double Derivator::FirstDerivative (double x) {
  
  // Ponto inválido
  if (x<min || x>max)
    throw invalid_argument(TString::Format("[%s] received invalid point!\n", __PRETTY_FUNCTION__));

  // Pontos centrais do domínio
  if (x-2*h>=min && x+2*h<=max)
    return ( (Eval(x-2*h) + 8*Eval(x+h)) - (8*Eval(x-h) + Eval(x+2*h)) ) / (12*h); // Five-point formula

  // Pontos em extremo inferior
  if (x-2*h<min && x-h>=min)
    return (Eval(x+h) - Eval(x-h)) / (2*h); // Central difference
  if (x-h<min)
    return (-Eval (x+2*h) + 4*Eval(x+h) - 3*Eval(x)) / (2*h); // Forward difference

  // Pontos em extremo superior
  if (x+2*h>max && x+h<=max)
    return (Eval(x+h) - Eval(x-h)) / (2*h); // Central difference
  if (x+h>max)
    return (Eval (x-2*h) - 4*Eval(x-h) + 3*Eval(x)) / (2*h); // Backward difference

  // Em caso de erro
  else
    throw invalid_argument(TString::Format("[%s] was unable to calculate the first derivative...\n", __PRETTY_FUNCTION__));
}

// Segunda derivada em todo o domínio
Func1D Derivator::Derivate2() {
  auto f = [this](double *x, double *par=nullptr)
	   {
	     return SecondDerivative (x[0]);
	   };
  return Func1D(new TF1("Second Derivative", f, min, max, 0));
}

// Segunda derivada em ponto x
double Derivator::SecondDerivative (double x) {
  
  // Ponto inválido
  if (x<min || x>max)
    throw invalid_argument(TString::Format("[%s] received invalid point!\n", __PRETTY_FUNCTION__));
    
  // Nota: Forward e backward differences, nos extremos, aqui: 'https://www.dam.brown.edu/people/alcyew/handouts/numdiff.pdf'

  // Pontos centrais do domínio
  if (x-2*h>=min && x+2*h<=max)
    return (-Eval (x-2*h) + 16*Eval(x-h) - 30*Eval(x) + 16*Eval(x+h) - Eval(x+2*h)) / (12*h*h); // 5-point formula

  // Pontos em extremo inferior
  if (x-2*h<min && x-h>=min)
    return (Eval (x+h) - 2*Eval(x) + Eval(x-h)) / (h*h); // 3-point formula
  if (x-h<min)
    return (2*Eval(x) - 5*Eval(x+h) + 4*Eval(x+2*h) - Eval(x+3*h))/(h*h*h); // Forward difference

  // Pontos em extremo superior
  if (x+2*h>max && x+h<=max)
    return (Eval (x+h) - 2*Eval(x) + Eval(x-h)) / (h*h); // 3-point formula
  if (x+h>max)
    return (2*Eval(x) - 5*Eval(x-h) + 4*Eval(x-2*h) - Eval(x-3*h))/(h*h*h); // Backward difference

  // Em caso de erro
  else
    throw invalid_argument(TString::Format("[%s] was given an invalid option... \n", __PRETTY_FUNCTION__));
}

// Nota: Fórmulas para third and fourth derivatives em 'https://www.geometrictools.com/Documentation/FiniteDifferences.pdf'

// Terceira derivada em todo o domínio
Func1D Derivator::Derivate3() {
  auto f = [this](double *x, double *par=nullptr)
	   {
	     return ThirdDerivative (x[0]);
	   };
  return Func1D(new TF1("Third Derivative", f, min, max, 0));
}

// Terceira derivada em ponto x
double Derivator::ThirdDerivative (double x) {
  double fator = 100.;
  // Ponto inválido
  if (x<min || x>max)
    throw invalid_argument(TString::Format("[%s] received invalid point!\n", __PRETTY_FUNCTION__));

  // Pontos centrais do domínio
  if (x-2*h>=min && x+2*h<=max)
    return (-Eval(x-2*h) + 2*Eval(x-h) - 2*Eval(x+h) + Eval(x+2*h))/(2*h*h*h); // Centered difference

  // Pontos em extremo inferior
  // if (x-2*h<min && x-h>=min)
  //return (-3*Eval(x-h) + 10*Eval(x) - 12*Eval(x+h) + 6*Eval(x+2*h) - Eval(x+3*h)/(2*h*h*h)); // Mixed forward difference
  if (x-2*h<min)
    return (-5*Eval(x) + 18*Eval(x+h) - 24*Eval(x+2*h) + 14*Eval(x+3*h) - 3*Eval(x+4*h))/(2*h*h*h); // Forward difference

  // Pontos em extremo superior
  //if (x+2*h>max && x+h<=max)
  //return (Eval(x-3*h) - 6*Eval(x-2*h) + 12*Eval(x-h) - 10*Eval(x) + 3*Eval(x+h))/(2*h*h*h); // Mixed backward difference
  if (x+2*h>max)
    return (3*Eval(x-4*h) - 14*Eval(x-3*h) + 24*Eval(x-2*h) - 18*Eval(x-h) + 5*Eval(x))/(2*h*h*h); // Backward difference

  // Em caso de erro
  else
    throw invalid_argument(TString::Format("[%s] was given an invalid option... \n", __PRETTY_FUNCTION__));
}

// Primeira derivada em todo o domínio
Func1D Derivator::Derivate4() {
  auto f = [this](double *x, double *par=nullptr)
	   {
	     return FourthDerivative (x[0]);
	   };
  return Func1D(new TF1("Fourth Derivative", f, min, max, 0));
}

// Segunda derivada em ponto x
double Derivator::FourthDerivative (double x) {
  
  // Ponto inválido
  if (x<min || x>max)
    throw invalid_argument(TString::Format("[%s] received invalid point!\n", __PRETTY_FUNCTION__));

  // Pontos centrais do domínio
  if (x-2*h>=min && x+2*h<=max)
    return (Eval(x-2*h) - 4*Eval(x-h) + 6*Eval(x) - 4*Eval(x+h) + Eval(x+2*h))/(h*h*h*h); // Centered difference
  
  // Pontos em extremo inferior
  if (x-2*h<min && x-h>=min)
    return (Eval(x-h) - 4*Eval(x) + 6*Eval(x+h) - 4*Eval(x+2*h) + Eval(x+3*h))/(h*h*h*h); // Mixed forward difference
  if (x-h<min)
    return (Eval(x) - 4*Eval(x+h) + 6*Eval(x+2*h) - 4*Eval(x+3*h) + Eval(x+4*h))/(h*h*h*h); // Forward difference

  // Pontos em extremo superior
  if (x+2*h>max && x+h<=max)
    return (Eval(x-3*h) - 4*Eval(x-2*h) + 6*Eval(x-h) - 4*Eval(x) + Eval (x+h))/(h*h*h*h); // Mixed backward difference
  if (x+h>max)
    return (Eval(x-4*h) - 4*Eval(x-3*h) + 6*Eval(x-2*h) - 4*Eval(x-h) + Eval(x))/(h*h*h*h); // Backward difference

  // Em caso de erro
  else
    throw invalid_argument(TString::Format("[%s] was given an invalid option... \n", __PRETTY_FUNCTION__));
}

// Mudar valor de h
void Derivator::SetH (double h1) {
  if (h1<=0.)
    throw invalid_argument(TString::Format("[%s] received a non positive h!\n", __PRETTY_FUNCTION__));
  h = h1;
}

// Fornecer o valor de h
double Derivator::GetH () const {
  return h;
}
