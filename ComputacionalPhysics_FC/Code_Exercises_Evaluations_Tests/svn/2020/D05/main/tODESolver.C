#include "ODESolver.h"
#include "ODEPoint.h"

#include <iostream>

#include "TF1.h"
#include "TMath.h"


using namespace std;


int main() {

  cout << "//////////////////////////////////\nEuler\n";
  //Euler
  TF1 f1 ("f1", [&](double* x, double* par){return TMath::Exp(x[0]-x[1]);}, 0, 10, 0);
  
  ODEPoint initial_condition(0.1,vector<double> ({1.03679}),1);

  cout << "\nCONDICAOINICIAL: " << initial_condition << endl;

  ODESolver solver (initial_condition, vector<TF1> ({f1}));

  double step = 0.1;
  double time = 0.2;
  vector<ODEPoint> solution = solver.EulerSolve(step, time);

  for(int i = 0; i < solution.size(); i++) {
    //cout << "t: " << solution[i] << endl;

    cout << "y(" << solution[i].getIndepVar() << ") = " << solution[i].getDepVar(0) << endl;

  }

  cout << "///////////////////////////////////////\nMidpoint / RK2\n";
  
  //Midpoint / RK2
  TF1 f2 ("f2", [&](double* x, double* par){return (2*TMath::Exp(x[0]) - x[1]) / (2 - x[1]);}, 0, 10, 0);
  
  ODEPoint initial_condition2(2,vector<double> ({0}),1);

  ODESolver solver2 (initial_condition2, vector<TF1> ({f2}));

  step = 0.2;
  time = 2.2;
  vector<ODEPoint> solution2 = solver2.RK2Solve(step, time);

  for(int i = 0; i < solution2.size(); i++) {

    cout << "y(" << solution2[i].getIndepVar() << ") = ";
    cout << solution2[i].getDepVar(0) << endl;

  }

  
  cout << "///////////////////////////////////////\nRK4\n";
  
  //RK4
  vector<ODEPoint> solution3 = solver2.RK4Solve(step, time);

  for(int i = 0; i < solution3.size(); i++) {

    cout << "y(" << solution3[i].getIndepVar() << ") = ";
    cout << solution3[i].getDepVar(0) << endl;

  }

  cout << "///////////////////////////////////////\nPredictor-Corrector\n";
  
  //RK4
  vector<ODEPoint> solution4 = solver2.PredictorCorrectorSolve(step, time);

  for(int i = 0; i < solution4.size(); i++) {

    cout << "y(" << solution4[i].getIndepVar() << ") = ";
    cout << solution4[i].getDepVar(0) << endl;

  }



  ////////////////SISTEMAS

  cout << "//////////////////////////////////////////\nSISTEMAS\n";
  TF1 f3 ("f3", [&](double* x, double* par){return x[2];}, 0, 10, 0);
  TF1 f4 ("f4", [&](double* x, double* par){return (-10*x[0]*(x[1]+x[2]));}, 0, 10, 0);

  step = 1;
  time = 10;

  ODEPoint initial_condition5(0,vector<double> ({1,0}),2);

  ODESolver solver5 (initial_condition5, vector<TF1> ({f3,f4}));

  vector<ODEPoint> solution5 = solver5.RK2Solve(step, time);

  cout << "\nRunge-Kutta 2nd Order:\n";
  for(int i = 0; i < solution5.size(); i++) {

    cout << "y(" << solution5[i].getIndepVar() << ") = ";
    cout << solution5[i].getDepVar(0);
    cout << ", y'(" << solution5[i].getIndepVar() << ") = ";
    cout << solution5[i].getDepVar(1) << endl;

  }

  vector<ODEPoint> solution6 = solver5.RK4Solve(step, time);

  cout << "\nRunge-Kutta 4th Order:\n";
  for(int i = 0; i < solution6.size(); i++) {

    cout << "y(" << solution6[i].getIndepVar() << ") = ";
    cout << solution6[i].getDepVar(0);
    cout << ", y'(" << solution6[i].getIndepVar() << ") = ";
    cout << solution6[i].getDepVar(1) << endl;

  }

  vector<ODEPoint> solution7 = solver5.EulerSolve(step, time);

  cout << "\nEuler\n";
  for(int i = 0; i < solution7.size(); i++) {

    cout << "y(" << solution7[i].getIndepVar() << ") = ";
    cout << solution7[i].getDepVar(0);
    cout << ", y'(" << solution7[i].getIndepVar() << ") = ";
    cout << solution7[i].getDepVar(1) << endl;

  }
  
  return 0;
}
