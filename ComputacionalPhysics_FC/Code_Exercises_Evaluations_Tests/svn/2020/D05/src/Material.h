#ifndef __Material__

#define __Material__

#include <string>
#include <TROOT.h>

using namespace std;

class Material {

 protected:

  string name;
  Double_t density;

 public:

  Material(string fname = "", Double_t fdens = 0);
  ~Material();
  string GetName();
  Double_t GetDensity();
  virtual void Print();

};

#endif
