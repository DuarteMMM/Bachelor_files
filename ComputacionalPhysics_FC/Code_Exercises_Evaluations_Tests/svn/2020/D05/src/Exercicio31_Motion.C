#include "Exercicio31_Motion.h"
#include <cstdio>
#include <cstdlib>

Motion1D::Motion1D (int N_a) : N(N_a){
  printf ("[%s] constructor called...\n", __PRETTY_FUNCTION__);
  x = new float[N_a];
  t = new float[N_a];
}

Motion1D::~Motion1D(){
  printf ("[%s] destructor called...\n", __PRETTY_FUNCTION__);
  free (t);
  free (x);
}

void Motion1D::SetMotion (float* t_a, float* x_a, int N_a){
  printf ("[%s] SetMotion called...\n", __PRETTY_FUNCTION__);
  int contador = 0;
  while (contador < N_a)
    {
      t[contador] = t_a[contador];
      x[contador] = x_a[contador];
      contador++;
    }
}

int Motion1D::GetN() const{
  printf ("[%s] GetN called...\n", __PRETTY_FUNCTION__);
  return N;
}

float* Motion1D::GetTimes() const{
  printf ("[%s] GetTimes called...\n", __PRETTY_FUNCTION__);
  return t;
}

float* Motion1D::GetPositions() const{
  printf ("[%s] GetPositions called...\n", __PRETTY_FUNCTION__);
  return x;
}

void Motion1D::Print (){
  printf ("[%s] Print called...\n", __PRETTY_FUNCTION__);
  int contador = 0;
  printf ("\nOs valores de x são:\n");
  while (contador < N)
    {
      printf ("%f\n", x[contador]);
      contador++;
    }
}

float Motion1D::TotalDistance(){
  float diferenca1 = x[N-1]-x[0];
  float diferenca2 = x[0]-x[N-1];
  if (diferenca1 >= 0.00001)
    return diferenca1;
  else
    return diferenca2;
}
  
float Motion1D::MeanVelocity(){
  float delta_x = TotalDistance();
  float tempo = t[N-1] - t[0];
  float velocidade_media = delta_x/tempo;
  return velocidade_media;
}
