#ifndef __ODEPOINT__
#define __ODEPOINT__

#include <vector>
#include <iostream>


using namespace std;


class ODEPoint {

public:

  //constructors and destructors
  ODEPoint();
  ODEPoint(double, vector<double>, int arg_n = 0);
  //ODEPoint(double, double*, int arg_n = 0);
  ODEPoint(const ODEPoint&);
  ~ODEPoint();
  

  //getters
  double getIndepVar();
  double getDepVar(unsigned int);
  vector<double> getDepVarVector();
  int size();


  //operators
  ODEPoint operator+(const ODEPoint&) const;


  //friends
  friend ostream& operator<< (ostream&, const ODEPoint&); 
  
private:

  int n;
  double* t; //independent variable
  vector<double> v; //dependent variables

};


#endif
