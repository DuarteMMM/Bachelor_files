#ifndef __OpticalMat__

#define __OpticalMat__


#include "Material.h"
#include <vector>
#include <utility>
#include "TF1.h"


using namespace std;


class OpticalMat : public Material {

  
public:

  OpticalMat();
  ~OpticalMat();

  void SetRefIndex(vector<pair<float, float> >);

  vector<pair<float, float> > GetRefIndex();

  void SetFitRefIndex(TF1*);

  TF1* GetFitRefIndex();
  /*
  void DrawRefIndexPoints();

  void DrawFitRefIndex();

  //void Print();
  */
  
private:

  // double FitRefIndex(double* x, double* par);

  TF1* f;
  vector<pair<float, float> > RefIndex;

};


#endif
