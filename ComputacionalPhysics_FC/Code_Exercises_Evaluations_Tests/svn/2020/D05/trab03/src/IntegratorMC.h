#ifndef __INTEGRATORMC__
#define __INTEGRATORMC__

#include "Integrator.h"
#include "TF1.h"

class IntegratorMC : public Integrator {

 public:
  IntegratorMC() = default;
  IntegratorMC(TF1* f) : Integrator(f, f->GetXmin(), f->GetXmax()) {}
  ~IntegratorMC() = default;

  void SimpleIntegration (int& N, double& value, double& error);

  void ImportanceSampling(int& N, double& value, double& error, const TF1& px, const TF1& xy); // N: number of randoms to generate; o integral é retornado em value. If error is passed to method as 0., it means that the integral error will be dictated by the number of randoms passed to the method and pdf(x) shape. Otherwise, the number of randoms will be defined by the error passed to the method.
  
  void AcceptanceRejection (int& N, double& value, double& error); 
  
  void AcceptanceRejectionAuxFunc (int& N, double& value, double& error, const TF1& q, const TF1& p);
  
  static std::vector<double> RandomGen(int, const TF1&);
};


#endif
