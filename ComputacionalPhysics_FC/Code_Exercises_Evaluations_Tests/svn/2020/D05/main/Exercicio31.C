/******************************************************
 *                Física Computacional                *
 *                    Exercício 31                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "Exercicio31_Motion.h"
#include "Exercicio31_Uniform.h"
#include <iostream>
using namespace std;

int main (){
  cout << "\n----- Exercício 30 -----\n\n";

  // ----------------> Alínea a
  // instanciar objeto Uniform1D
  Uniform1D *p1D = new Uniform1D (100, 0., 0., 10., 10.); // Pus 10. em dt porque se quer 1000 segundos em 100 pontos
  p1D->Print();

  // ----------------> Alíneas b e c
  // make an array with Motion1D derived objects
  Motion1D* pm[2] = {
		     new Uniform1D (100, 0., 0., 0.1, 20.), // dt no enunciado mal???
		     new Motion1D(400)
  };
  // fill Motion1D object with values
  float* t = new float[400];
  float* x = new float[400];
  // Supus que a altura inicial é o zero do referencial e o sentido para baixo
  // A velocidade inicial é zero
  // A posição é dada por 0.5*g*t*t
  int contador=0;
  float t_valor = 0.;
  float x_valor = 0.;
  while (contador < 400)
    {
      t[contador] = t_valor;
      x[contador] = x_valor;
      t_valor += 0.1;
      x_valor = 0.5*9.8*t_valor*t_valor;
      contador++;
    }

  (*pm[1]).SetMotion(t, x, 400); // Dar este movimento de queda livre ao elemento de pm

  (*pm[0]).Print();
  (*pm[1]).Print();

  // ----------------> Alínea d
  // O enunciado para a inicialização desta nova alínea está pouco claro... Aliás, para a outra também estava...
  Motion1D m[2] = {
		   Motion1D (400),
		   Motion1D (400)
  };
  m[0].SetMotion (t, x, 400);
  m[0].Print();
  float* t2 = new float[400];
  float* x2 = new float[400];
  // Supus que a altura inicial é o zero do referencial e o sentido para baixo
  // A velocidade inicial é -1 m/s
  // A posição é dada por -1*t + 0.5*g*t*t
  contador=0;
  float t_valor2 = 0.;
  float x_valor2 = 0.;
  while (contador < 400)
    {
      t2[contador] = t_valor2;
      x2[contador] = x_valor2;
      t_valor2 += 0.1;
      x_valor2 = -t_valor2 + 0.5*9.8*t_valor2*t_valor2;
      contador++;
    }
  m[1].SetMotion(t2, x2, 400); // Dar este movimento de queda livre de velocidade inicial -1 ao elemento de m

  // ----------------> Alínea e
  // Nota: verificou-se que os valores de m são automaticamente destruídos...
  delete p1D;
  delete pm[0];
  delete pm[1];
  delete t;
  delete t2;
  delete x;
  delete x2;
 
  return 0;
}
