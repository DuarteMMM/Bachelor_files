#ifndef __ODESOLVER__
#define __ODESOLVER__

#include "ODEPoint.h"

#include "TF1.h"

#include <vector>


using namespace std;


class ODESolver {

public:

  //constructors and destructors
  ODESolver() = default;
  ODESolver(const ODEPoint&, const vector<TF1>&);
  ODESolver(const ODESolver&);
  
  ~ODESolver() = default;

  
  //solvers
  vector<ODEPoint> EulerSolve(double, double); //step size, time
  vector<ODEPoint> LeapFrogSolve (double, double);
  vector<ODEPoint> RK2Solve (double, double); //Midpoint method
  vector<ODEPoint> RK4Solve (double, double);
  vector<ODEPoint> PredictorCorrectorSolve (double, double);
  vector<double> LoopVerletIterate (double, int, vector<double>, vector<double>);

  
private:

  vector<TF1> functions;
  ODEPoint initial_values;
  
};



#endif
