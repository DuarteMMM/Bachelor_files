#include "Func1D.h"
#include "Derivator.h"
#include "Integrator.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "TString.h"


using namespace std;


////////////////////////////// Constructors


Integrator::Integrator() : Func1D(), xmin(0), xmax(0) {}


Integrator::Integrator(TF1* func, double a, double b) : Func1D(func), xmin(a), xmax(b) {}


Integrator::Integrator(const Integrator& i) : Integrator(i.f, i.xmin, i.xmax) {}


////////////////////////////// Integration methods


void Integrator::Trapezoidal(int n, double& integral, double& error) {

  if (n < 1)
    throw invalid_argument(TString::Format("[%s]: there must be at least 1 interval!\n", __PRETTY_FUNCTION__));
    
  double h = (xmax-xmin)/n; // Comprimento de cada subintervalo
  Derivator d(f);

  integral = 0.;
  
  for(int i = 0; i < n; i++)
    {
      integral += (Eval(xmin + i*h) + Eval(xmin + (i+1)*h)) * h/2;
      error += d.SecondDerivative(xmin + (i+0.5)*h); // Segunda derivada no meio de cada subintervalo
      //error += (d.FirstDerivative(xmin + (i+1)*h) - d.FirstDerivative(xmin + i*h))/h;
    }

  error /= n;
  error *= (-h*h*(xmax-xmin)/12);

  //Outra forma de calcular o erro
  //Func1D SegDeriv = d.Derivate2();
  //error = (-SegDeriv.GetMaxValue()*h*h*(xmax-xmin)) / 12;

}


void Integrator::TrapezoidalAdaptative (int& N, double& integral, double& error) {
 
  if (N < 2)
    throw invalid_argument(TString::Format("[%s] must receive a maximum k of at least 2...\n", __PRETTY_FUNCTION__));

  bool bN = true;

  // Se error>0., o número de iterações (N) será determinado pelo erro relativo pretendido (error)
  if (error > 0.) {
    N = 0;
    bN = false;
  }
  
  integral = ((xmax-xmin)/2.)*(Eval(xmin)+Eval(xmax)); // Valor para k=1
  double valor; // Integral calculado para k, a partir do de k-1
  int k=2; // Valor inicial de k

  double error_iter = integral*error + integral; // Erro ao longo do ciclo (pus este valor inicial para garantir que se faz no mínimo 1 ciclo
  double copia_integral;

  // Calcular as sucessivas aproximações do integral
  while ( (bN && k <= N) || (!bN && abs(error_iter/integral) > error) ) {
    
      valor = 0.;
      for (int i=1; i<=pow(2, k-2); i++)
	valor += Eval(xmin + (2*i-1)*((xmax-xmin)/pow(2, k-1)));
      valor = 0.5*integral + ((xmax-xmin)/pow(2, k-1))*valor;
      copia_integral = integral;
      integral = valor;
      k++;

      error_iter = abs(integral-copia_integral);  // Esta diferença dá uma boa estimativa do erro
      
    }

  N = k-1; // Número de iteradas realizadas (incluindo a para k=1)

  if (error > 0.)
    error = abs(error_iter/integral); // Erro final
  else
    error = error_iter;
}


void Integrator::Simpson(int n, double& integral, double& error) {
  
  // n should be even, but we can still calculte the integral when it's not...
  //throw invalid_argument(TString::Format("[%s] received odd number of intervals (must be even)", __PRETTY_FUNCTION__));

  Derivator d(f, 0.1); // Atenção ao valor de h que se dá!
  Func1D QuartaDeriv = d.Derivate4();
  double h = (xmax-xmin)/n;

  // n par
  if (n % 2 == 0) {
    // Integral para cada trio de slices
    for(int i = 0; i < n/2; i++)
      integral += (Eval(xmin + 2*i*h) + 4*Eval(xmin + 2*i*h + h) + Eval(xmin + 2*i*h + 2*h)) * h/3;
  }

  // n ímpar
  if (n % 2 == 1) {
    // Integrar para cada trio de slices
    for(int i = 0; i < (n-1)/2; i++)
      integral += (Eval(xmin + 2*i*h) + 4*Eval(xmin + 2*i*h + h) + Eval(xmin + 2*i*h + 2*h)) * h/3;

    // Integrar o trecho final
    integral += (h/12) * (-Eval(xmin+(n-2)*h) + 8*Eval(xmin+(n-1)*h) + 5*Eval(xmin+n*h)); 
  }

  error = (-QuartaDeriv.GetMaxValue()*(xmax-xmin)*h*h*h*h) / 180; // Coloquei sinal negativo tendo em conta a matéria lecionada em MC
}


void Integrator::Romberg (int& steps, int& level, double& integral, double& error) {
  
  if (level>steps)
    throw invalid_argument(TString::Format("[%s] desired level of integration requires higher number of steps (so that steps >= level)", __PRETTY_FUNCTION__));

  else {

    if (error == 0.) {

      // Criar a matriz (triangular inferior) necessária
      double **result = new double*[steps];
      for (int i=0; i<steps; i++)
	result[i] = new double[i+1];

      double valor = 0.;
      double var_erro = 0.;

      int nsteps_trapezoidal = 1;
      // Calcular todos os elementos da primeira coluna da matriz (simplesmente com regra trapezoidal)
      for (int contador_steps=0; contador_steps<steps; contador_steps++)
	{
	  valor = 0.;
	  var_erro = 0.;
	  Trapezoidal (nsteps_trapezoidal, valor, var_erro);
	  nsteps_trapezoidal *= 2;
	  result[contador_steps][0] = valor;
	}

    
      // Calcular os outros elementos da matriz, por linha (utilizando elementos à sua esquerda na matriz)
      for (int contador_steps=1; contador_steps<steps; contador_steps++)
	{
	  for (int contador_level=1; contador_level < level && contador_level <= contador_steps; contador_level++)
	    result[contador_steps][contador_level] = result[contador_steps][contador_level-1] + 1/(pow(4,contador_level)-1) * (result[contador_steps][contador_level-1] - result[contador_steps-1][contador_level-1]);
	}

      integral = result[steps-1][level-1]; // Guardar o valor
    
      error = result[steps-1][0] + var_erro - integral; // Pois I = I(h1) + E(h1) = I(h2) + E(h2), e error=E(h2)

      // Apagar a matriz
      for (int i=0; i<steps; i++)
	delete result[i];
      delete []result;
      
    } else {

      double calc_error = abs(error) + 1.; //só para ser maior que o erro a cumprir e portanto o ciclo iniciar

      // Criar a matriz (triangular inferior) necessária
      vector<double*> result;
      double valor = 0.;
      double var_erro = 0.;
      int contador_steps = 0;
      int contador_level = 0; //contador de nível a usar nos cálculos
      int nsteps_trapezoidal = 1;
      
      while (abs(error) < abs(calc_error)) {

	double* line = new double[contador_steps+1];
	result.push_back(line);
	
	valor = 0.;
	var_erro = 0.;
	Integrator::Trapezoidal (nsteps_trapezoidal, valor, var_erro);
	result[contador_steps][0] = valor;

	double multiplier = 1.;
	
	// Calcular os outros elementos da matriz, por linha (utilizando elementos à sua esquerda na matriz)
	for (contador_level=1; contador_level <= contador_steps; contador_level++)
	  {
	    multiplier *= 4;
	    double term = 1/(multiplier-1) * (result[contador_steps][contador_level-1] - result[contador_steps-1][contador_level-1]);
	    result[contador_steps][contador_level] = result[contador_steps][contador_level-1] + term;
	  }
	
	contador_level--; //para ficar no último valor em que conseguiu passar a condição

	integral = result[contador_steps][contador_level]; // Guardar o valor

	calc_error = abs((result[contador_steps][0] + var_erro - integral)/integral); // Pois I = I(h1) + E(h1) = I(h2) + E(h2), e error=E(h2)
	
	contador_steps++;
	nsteps_trapezoidal *= 2;
	
      }

      error = calc_error;
      steps = contador_steps;
      level = contador_level;
      
    }
  } 
}


/////////////////////////////// Operators


Integrator Integrator::operator+() {
  return *this;
}


Integrator Integrator::operator-() {
  // to be noticed that xmax and xmin are swapped when compared to the regular constructor
  return Integrator(this->f, this->xmax, this->xmin);

}


///////////////////////////////// Other methods


double Integrator::GetXMin() const {
  return xmin;

}


double Integrator::GetXMax() const {
  return xmax;
}

void Integrator::SetXMin(double value) {
  xmin = value;
}


void Integrator::SetXMax(double value) {
  xmax = value;
}


///////////////////////////////// friends


ostream& operator<< (ostream& s, const Integrator& i) {
  s << "Integration between " << i.GetXMin() << " and " << i.GetXMax() << "." << endl;
  return s;
}
