#include "Exercicio31_Uniform.h"
#include <cstdio>

Uniform1D::Uniform1D (int fN, float ti_a, float xi_a, float dt_a, float vel_a) : Motion1D (fN) {
  ti = ti_a;
  xi = xi_a;
  dt = dt_a;
  vel = vel_a;
  printf ("[%s] Uniform1D constructor called...\n", __PRETTY_FUNCTION__);
  float coor_x;
  float coor_t;
  coor_x = xi;
  coor_t = ti;
  // t and x arrays are created by Motion1D constructor
  for (int i=0; i<N; i++){
    t[i] = coor_t;
    x[i] = coor_x;
    coor_t += dt;
    coor_x = xi + vel*coor_t;
  }
}

void Uniform1D::Print(){
  printf ("[%s] Uniform1D Print called...\n", __PRETTY_FUNCTION__);
  Motion1D::Print(); // call Print from base class
  printf ("ti=%f, xi=%f, vel=%f \n", ti, xi, vel);
}
