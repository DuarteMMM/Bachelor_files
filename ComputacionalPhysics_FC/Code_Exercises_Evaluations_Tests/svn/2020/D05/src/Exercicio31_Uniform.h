#ifndef __uniform__
#define __uniform__
#include "Exercicio31_Motion.h"

class Uniform1D : public Motion1D{
public:
	Uniform1D (int fN=0, float ti_a=0., float xi_a=0., float dt_a=0., float vel_a=0.);
	~Uniform1D()=default;
	
	void Print();
	
private:
	float ti; // initial time
	float dt; // time duration
	float xi; // initial position
	float vel; // velocity (m/s)
};	


#endif
