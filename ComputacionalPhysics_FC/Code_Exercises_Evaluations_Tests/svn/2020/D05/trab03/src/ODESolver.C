#include "ODESolver.h"
#include "ODEPoint.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <utility>

#include "TF1.h"

//#define DEBUG


using namespace std;


////////////////////////////////constructors and destructors
//ODESolver::ODESolver() default


ODESolver::ODESolver(const ODEPoint& p, const vector<TF1>& f) : initial_values(p), functions(f) {}


ODESolver::ODESolver(const ODESolver& s) : ODESolver(s.initial_values, s.functions) {}


//ODESolver::~ODESolver() default


///////////////////////////////solvers


vector<ODEPoint> ODESolver::EulerSolve(double step, double time) {

  int n_functions = functions.size();
  double init_time = initial_values.getIndepVar();
  int n_steps = (time - init_time)/step;
  
  vector<ODEPoint> result;
  result.push_back(initial_values);
  
  for(int i = 1; i <= n_steps; i++) {

    vector<double> vec; 
    
    vector<double> prev = result[i-1].getDepVarVector();
    prev.emplace(prev.begin(), result[i-1].getIndepVar());

    vec.push_back(prev[0] + step);
    
    for(int j = 0; j < n_functions; j++) {

      /*cout << prev[j] << endl;
      cout << step << endl;
      cout << functions[j].EvalPar(&(prev[0])) << endl;*/
      vec.push_back(prev[j+1] + step * functions[j].EvalPar(&(prev[0])));

    }

    vec.erase(vec.begin());
    
    ODEPoint newpoint (i * step + init_time, vec);
    result.push_back(newpoint);
    
  }

  return result;
}


//Midpoint Method
vector<ODEPoint> ODESolver::RK2Solve (double step, double time) {

  int n_functions = functions.size();
  double init_time = initial_values.getIndepVar();
  int n_steps = (time - init_time)/step;
  
  vector<ODEPoint> result;
  result.push_back(initial_values);

  for(int i = 1; i <= n_steps; i++) {
    
    vector<double> current;
    vector<double> intermediate;
    vector<double> prev = result[i-1].getDepVarVector();
    prev.emplace(prev.begin(), result[i-1].getIndepVar());

    current.push_back(prev[0] + step);
    intermediate.push_back(prev[0] + step/2);

    
    for(int j = 0; j < n_functions; j++) {

      //cout << prev[j+1] + step/2 * functions[j].EvalPar(&(prev[0])) << endl;
      intermediate.push_back(prev[j+1] + step/2 * functions[j].EvalPar(&(prev[0])));

    }

    for(int k = 0; k < n_functions; k++) {

      /*cout << prev[k+1] << endl;
      cout << step << endl;
      cout << functions[k].EvalPar(&(intermediate[0])) << endl;
      cout << intermediate[0] << endl;
      cout << intermediate[1] << endl;
      cout << (2*TMath::Exp(intermediate[0]) - intermediate[1])/(2-intermediate[1]) << endl;
      cout << prev[k+1] + step * functions[k].EvalPar(&(intermediate[0])) << endl;*/
      current.push_back(prev[k+1] + step * functions[k].EvalPar(&(intermediate[0])));
      
    }

    current.erase(current.begin());

    ODEPoint newpoint (i * step + init_time, current);
    result.push_back(newpoint);
    
  }

  return result;
}


vector<ODEPoint> ODESolver::RK4Solve (double step, double time) {

  int n_functions = functions.size();
  double init_time = initial_values.getIndepVar();
  int n_steps = (time - init_time)/step;
  
  vector<ODEPoint> result;
  result.push_back(initial_values);

  for(int i = 1; i <= n_steps; i++) {
    
    
    
    vector<double> estimate1, estimate2, estimate3, estimate4;
    vector<double> prev = result[i-1].getDepVarVector();
    prev.emplace(prev.begin(), result[i-1].getIndepVar());

    vector<double> current = prev; //guarda o tempo e o valor das 'n_functions' variáveis para esse tempo
    
    current[0] += step;

    estimate1.push_back(prev[0] + step/2);
    estimate2.push_back(prev[0] + step/2);
    estimate3.push_back(prev[0] + step);
    
    for(int j = 0; j < n_functions; j++) {

      double k1 = step * functions[j].EvalPar(&(prev[0]));

      estimate1.push_back(prev[j+1]+k1/2);

      current[j+1] += k1/6; 
    }

    for(int j = 0; j < n_functions; j++) {

      double k2 = step * functions[j].EvalPar(&(estimate1[0]));

      estimate2.push_back(prev[j+1]+k2/2);

      current[j+1] += k2/3;
    }

    for(int j = 0; j < n_functions; j++) {

      double k3 = step * functions[j].EvalPar(&(estimate2[0]));

      estimate3.push_back(prev[j+1]+k3);

      current[j+1] += k3/3;
    }

    for(int j = 0; j < n_functions; j++) {

      double k4 = step * functions[j].EvalPar(&(estimate3[0]));

      current[j+1] += k4/6;
    }
    
    current.erase(current.begin());

    ODEPoint newpoint (i * step + init_time, current);
    result.push_back(newpoint);
    
  }

  return result;

}


vector<ODEPoint> ODESolver::PredictorCorrectorSolve (double step, double time) {

  int n_functions = functions.size();
  double init_time = initial_values.getIndepVar();
  int n_steps = (time - init_time)/step;
  
  vector<ODEPoint> result;
  result.push_back(initial_values);
  
  for(int i = 1; i <= n_steps; i++) {

    vector<double> prevslope, currentslope, current, eulerpred;
    vector<double> prev = result[i-1].getDepVarVector();
    prev.emplace(prev.begin(), result[i-1].getIndepVar());

    current.push_back(prev[0] + step);
    eulerpred.push_back(prev[0] + step);
    
    for(int j = 0; j < n_functions; j++) {

      prevslope.push_back(functions[j].EvalPar(&(prev[0])));
      eulerpred.push_back(prev[j+1] + step * prevslope[j]);
	
    }

    for(int j = 0; j < n_functions; j++) {

      currentslope.push_back(functions[j].EvalPar(&(eulerpred[0])));
      
      current.push_back(prev[j+1] + step/2 * (currentslope[j] + prevslope[j]));
      
    }

    current.erase(current.begin());
    
    ODEPoint newpoint (i * step + init_time, current);
    result.push_back(newpoint);
    
  }

  return result;
  
}


/*
vector<ODEPoint> ODESolver::LoopVerletSolve (double step, double time, ODEPoint firstpoint) {

  int n_functions = functions.size();
  double init_time = initial_values.getIndepVar();
  int n_steps = (time - init_time)/step;

  //inserir y(0) no vetor de resultados
  vector<ODEPoint> result;
  result.push_back(initial_values);
  result.push_back(firstpoint);

  /*
  //cálculo do y(h)
  vector<double> initial = initial_values.getDepVarVector();
  initial.emplace(initial.begin(), init_time);
  vector<double> firststep;

  //cout << prev[j] << endl;
  //cout << step << endl;
  //cout << functions[j].EvalPar(&(prev[0])) << endl;
  //firststep.push_back(log(exp(2 * initial[1]) / exp(initial[1] - step * initial[2]) + step*step/2*functions[0].EvalPar(&initial[0])) + step*step*functions[0].EvalPar(&initial[0]));

  firststep.push_back(2 * initial[1] - initial[1] + step * initial[2] - step*step/2*functions[0].EvalPar(&initial[0]) + step*step*functions[0].EvalPar(&initial[0]));

  cout << initial[2] << endl;

  ODEPoint firstpoint (init_time+step, firststep);
  result.push_back(firstpoint);
  

  
  //loop automático para calcular y(i*h), i>1
  for(int i = 2; i <= n_steps; i++) {

    vector<double> current = result[i-1].getDepVarVector(); //última iteração já calculada
    current.emplace(current.begin(), result[i-1].getIndepVar());
    vector<double> next; //iteração que vai ser calculada agora
    vector<double> prev = result[i-2].getDepVarVector(); //iteração anterior ao current
    //prev.emplace(prev.begin(), result[i-2].getIndepVar());

    //next.push_back(current[0] + step);
   
    for(int j = 0; j < n_functions; j++) {
      /*cout << prev[j] << endl;
	cout << step << endl;
	cout << functions[j].EvalPar(&(prev[0])) << endl;
      next.push_back(2 * current[j+1] - prev[j] + step*step*functions[j].EvalPar(&(current[0]), j/2) );
    }

    //next.erase(next.begin());
    
    ODEPoint newpoint (i * step + init_time, next);
    result.push_back(newpoint);
    
  }

  return result;
  
}
*/

//current - últimas posições/velocidades calculadas; previous - posições/velocidades imediatamente anteriores a current
vector<double> ODESolver::LoopVerletIterate (double step, int halfsize, vector<double> prev, vector<double> current) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  
  vector<double> result(halfsize * 2, 0.);

#ifdef DEBUG
  cout << "Halfsize: " << halfsize << endl;
#endif

  for(int i = 0; i < halfsize; i++) {

#ifdef DEBUG
    cout << "Entrou no loop vez " << i << endl;
#endif
    
    double i_double = (double) i;
    
    double accel_x = functions[0].EvalPar(&(current[0]), &i_double);
    double accel_y = functions[1].EvalPar(&(current[0]), &i_double);

    //cout << "i_double = " << i_double << ", " << accel_x << ", " << accel_y << endl;
    //cout << current[i] << ", " << prev[i] << ", " << current[i+halfsize] << ", " << prev[i+halfsize] << endl;
    result[i] = 2. * current[i] - prev[i] + step*step*accel_x;
    result[i+halfsize] = 2. * current[i+halfsize] - prev[i+halfsize] + step*step*accel_y;

    //cout << i << "ª:" << "x[i]: " << result[i] << ", y[i]: " << result[i] << ", accel_x: " << accel_x << ", accel_y: " << accel_y << endl; AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    
    //result[i] = (2 * current[i] - prev[i] + step*step*functions[0].EvalPar(&(current[0]), i) );
    //result[i+N] = (2 * current[i+N] - prev[i+N] + step*step*functions[1].EvalPar(&(current[0]), i) );
    
  }

  //cout << endl; AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
  return result;
  
}
