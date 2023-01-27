#include "ODEPoint.h"

#include "TString.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <array>


using namespace std;


///////////////////////////////////////////constructors


ODEPoint::ODEPoint() : n(-1), t(nullptr) {}


ODEPoint::ODEPoint(double arg_t, vector<double> arg_v, int arg_n) : v(arg_v), t(new double(arg_t)), n(arg_n) {

  if (v.size() > n) {

    n = v.size();

  }
  
}


/*ODEPoint::ODEPoint(double arg_t, double* arg_v, int arg_n) : v(arg_v), t(new double(arg_t)), n(arg_n) {

  if (v.size() > n) {

    n = v.size();

  }
  
  }*/


ODEPoint::ODEPoint(const ODEPoint& o) : ODEPoint(*(o.t), o.v, o.n) {}


ODEPoint::~ODEPoint() {

  delete t;
  
}


////////////////////////////////////getters


double ODEPoint::getIndepVar() {

  if (t != nullptr) {

    return *t;

  } else {

    throw invalid_argument(TString::Format("[%s] called with undefined independent variable.", __PRETTY_FUNCTION__));
    
  }

}


double ODEPoint::getDepVar(unsigned int index) {

  if (index < n) {

    return v[index];

  } else {

    throw invalid_argument(TString::Format("[%s] received invalid dependent variable index.", __PRETTY_FUNCTION__));
    
  }

}


vector<double> ODEPoint::getDepVarVector() {

  return v;

}


int ODEPoint::size() {

  return n;

}


/////////////////////////////////operators


ODEPoint ODEPoint::operator+(const ODEPoint& added) const {

  if (n == added.n) {

    vector<double> result = v;
    
    for(int i = 0; i < n; i++) {

      result[i] += added.v[i];

    }
    
    return ODEPoint(*t + *(added.t), result, n);

  } else {

    throw invalid_argument(TString::Format("[%s] called with different sized points.", __PRETTY_FUNCTION__));

  }

}


/////////////////////////////////friends


ostream& operator<< (ostream& s, const ODEPoint& p) {

  s << "Number of dependent variables: " << p.n << endl;
  s << "Independent variable = " << p.t << endl;

  for(int i = 0; i < p.n; i++) {

    s << "Dependent variable " << i+1 << " = " << p.v[i] << endl;

  }

  s << endl;

  return s;
}
