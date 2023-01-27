#include "Func1D.h"
#include "Derivator.h"
#include "Integrator.h"
#include "IntegratorMC.h"
#include "Spline3Interpolator.h" // Para Derivatives com Spline3

#include "TMath.h"
#include "TF1.h"
#include "TApplication.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TRandom.h"

#include <cmath>

#include <iostream>

#include "TFile.h"

using namespace std;

int main() {

  ////////////////////////////////////// Func1D
  cout << "\nFUNC1D" << endl;
  // Função 1
  // instantiate object Func1D
  auto f = [](double *x, double *par=nullptr)
	   {
	     return sin(x[0])/x[0] + 0.5*cos(0.5*x[0]);
	   };

  // Valor verdadeiro do integral: 0.5494996891767808

  // Criar Func1Ds
  Func1D F1(new TF1("F1",f, 0.1, 10., 0)); // constructor 1
  Func1D F2(TF1("F2", f, 0.1, 10., 0)); // constructor 2
  Func1D F3(F2); // Copy constructor

  
  // Eval: output - valores da função
  cout << "\nFunção Eval():" << endl;
  for (double a=0.1; a<1; a+=0.1) {
    cout << "x=" << a << ": " << f(&a) << " " << F1.Eval(a) << " " << F2.Eval(a) << endl;
  }

  // Alterar Func1Ds
  auto f2 = [](double *x, double *par=nullptr)
	    {
	      return sin(x[0]);
	    };
  // Mudar a função com SetFunc
  F1.SetFunc (new TF1("F1_change", f2, 1., 10., 0));
  
  // drawing
  //F1.Draw();
  //F2.Draw();
  //F3.Draw();

  /////////////////////////////////// Derivator

  cout << "\nDERIVATOR" << endl;

  Derivator teste_nulo();
  
  double h=1.e-5;
  // Criar Derivator com h e option default (h=1.e-5, option=0)
  Derivator d(new TF1("D1", f2, 0., 10., 0), h);
 
  // Calcular primeira derivada, desenhar gráfico e apresentar valores
  Func1D Derivative = d.Derivate1();
  //Derivative.Draw();
  cout << "\nPrimeira derivada do seno de 0 a 10" << endl;
  for (double a=0.; a<=9.; a+=1.)
    cout << "x=" << a << ": " << Derivative.Eval(a) << endl;
  cout << "\nPrimeira derivada do seno de 0 a 10 de outra forma" << endl;
  for (double a=0.; a<=9.; a+=1.)
    cout << "x=" << a << ": " << d.FirstDerivative(a) << endl;

  // Testar o copy constructor da classe Derivator
  Derivator copy_d (d);
  Func1D Derivative_copy = copy_d.Derivate1();
  //Derivative_copy.Draw();
  
  // Calcular segunda derivada, desenhar gráfico e apresentar valores
  Func1D Derivative2 = d.Derivate2();
  //Derivative2.Draw();
  cout << "\nSegunda derivada do seno de 0 a 10" << endl;
  for (double a=0.; a<=9.; a+=1.)
    cout << "x=" << a << ": " << Derivative2.Eval(a) << endl;

  // Calcular a terceira e quarta derivada, derivando em 2ªordem a 1ª derivada e a 2ªderivada, respetivamente->Neste exemplo, calculei fazendo sucessivas derivadas da primeira derivada, na melhor opcao, e mesmo assim a quarta derivada dava mal, logo fiz função para 3ª e 4ªderivadas na classe

  // Importante: MUDAR O H, senão dá gráficos maus
  
  // Calcular terceira derivada, desenhar gráfico e apresentar valores
  d.SetH (0.05);
  Func1D Derivative3 = d.Derivate3();
  //Derivative3.Draw();
  cout << "\nTerceira derivada do seno de 0 a 10" << endl;
  for (double a=0.; a<=9.; a+=1.)
    cout << "x=" << a << ": " << Derivative3.Eval(a) << endl;
  
  // Calcular quarta derivada, desenhar gráfico e apresentar valores
  d.SetH (0.1);
  Func1D Derivative4 = d.Derivate4();
  //Derivative4.Draw();
  cout << "\nQuarta derivada do seno de 0 a 10" << endl;
  for (double a=0.; a<=9.; a+=1.)
    cout << "x=" << a << ": " << Derivative4.Eval(a) << endl;
  
  
  ////////////////////////////////// Integrator

  // Nota: Função do ROOT para ver o integral: TF1 f ... e depois f.Integral(xmin, xmax))
  //Atenção! Com a função que tem sen(x)/x, se integrarmos perto do zero, o erro vai dar bastante grande

  //Entre 5 e 15, o valor verdadeiro do integral é: −0.1244198763501654
  cout << "\nINTEGRATOR" << endl;
  Integrator i1 (new TF1("F4", f2, 5., 20., 0), 5., 20.);

  TF1* function = new TF1("F4", f2, 5., 20., 0);
  cout << "Integral ROOT: " << function->Integral(5., 20.) << endl;
  
  double valor = 0.;
  double erro = 0.;
  i1.Trapezoidal(20, valor, erro);
  printf ("\n->Trapezoidal\nIntegral: %.10lf ; Erro: %.10lf\n", valor, erro);

  valor = 0.;
  erro = 0.000001; // Erro relativo desejado, se >0.
  int N_trap=10;
  i1.TrapezoidalAdaptative(N_trap, valor, erro);
  printf ("\n->TrapezoidalAdaptative\nIntegral: %.10lf ; Erro relativo: %.10lf ; Iterações: %d\n", valor, erro, N_trap);
  
  valor = 0.;
  erro = 0.;
  i1.Simpson(99, valor, erro);
  printf ("\n->Simpson\nIntegral: %.10lf ; Erro: %.10lf\n", valor, erro);

  int steps = 20;
  int level = 1;
  valor = 0.;
  erro = 0.;
  i1.Romberg(steps, level, valor, erro);
  printf ("\n->Romberg (20, 1):\nIntegral: %.10lf ; Erro: %.20lf\n", valor, erro);

  steps = 20;
  level = 10;
  valor = 0.;
  erro = 0.;
  i1.Romberg(steps, level, valor, erro);
  printf ("\n->Romberg (20, 10):\nIntegral: %.10lf ; Erro: %.20lf\n", valor, erro);

  steps = 10;
  level = 10;
  valor = 0.;
  erro = 0.;
  i1.Romberg(steps, level, valor, erro);
  printf ("\n->Romberg(10, 10):\nIntegral: %.10lf ; Erro: %.20lf\n", valor, erro);

  steps = 10;
  level = 10;
  valor = 0.;
  erro = 10e-3; // Erro relativo desejado
  i1.Romberg(steps, level, valor, erro);
  printf ("\n->Romberg (erro < 10e-03):\nIntegral: %.10lf ; Erro relativo: %.10lf ; Steps: %d ; Level: %d\n", valor, erro, steps, level);

  cout << "\nTeste de outros métodos\n->GetXMin(): " << i1.GetXMin() << "\n->GetXMax(): " << i1.GetXMax() << "\n->Operador <<: " << i1;

  
  
  ///////////////////////// IntegratorMC
  
  cout << "\nINTEGRATORMC" << endl;
  
  // Integration limits
  double xlow = 0.1;
  double xup = 10.;

  TF1 *G = new TF1 ("G", f, xlow, xup, 0); // npar=0, ndim=1 (default)
  G->SetNpx (1000); // Set the number of points used to draw the function

  // Auxiliary functions
  // COM UNIFORM PDF!!! (normalized->probabilidade total é 1): $\int_{x_1}^{x_2} k dx = 1 \Rightarrow k = 1/(x_2 - x_1)$
  // Pois se x está uniformely distributed, então p(x)=1 (a probabilidade é sempre 1 num qualquer x), logo k*(integral de a a b) de p(x) = 1 implica que k é 1/(b-a) (sendo b=x_2 e a=x_1, nas notações anteriores)

  // Isto é a função probabilidade normalizada (ou seja, com o k), que irá ser calculada nos y_i (aleatórios entre 0 e 1); está no denominador da expressão dos slides
  auto p = [xlow, xup](double* x, double* par) {
	     return 1./(xup-xlow);
	   };

  TF1 P("P", p, xlow, xup, 0); // npar=0, ndim=1 (default)
  P.SetNpx(1000);

  // ...pdf cumulative and inverted: $y = \int_{x_1}^{x} k*p(x) dx  = \frac{x - x_1}{x_2 - x_1} \Rightarrow x = x_1 + y * [x_2 - x_1]$ -> Obter o x a partir do y, que é dado por k*(integral indefinido de a a x) de p(x), PORQUE k*(integral indefinido de a a x) É O "NOVO INTEGRAL", O INTEGRAL NORMALIZADO

  // Isto é a função x (obteve-se em cima a inversa, que é este x), onde se vão calcular x(y_i), sendo y_i os aleatórios entre 0 e 1; estes x(y_i) estão no numerador da expressão dos slides
  auto pi = [xlow, xup](double* x, double* par) {
	      return xlow + x[0]*(xup-xlow);
	    };

  TF1 PI ("PI", pi, xlow, xup, 0); // napr=0, ndim=1 (default)
  PI.SetNpx (1000);


  // Simple Integration
  TH1F H1("H1", "SimpleIntegration", 100, 0, 2);
  int N = 1000; // O SimpleIntegration não altera o valor de N
  IntegratorMC I(G);
  for (int i=0; i<2000; ++i) {
    double value = 0.;
    double error = 0.;
    I.SimpleIntegration (N, value, error);
    H1.Fill(value);
    //cout << "Valor: " << value << endl;
    //cout << "Erro: " << error << endl;
  }

  // Importance sampling
  TH1F H2("H2", "ImportanceSampling", 100, 0, 2);
  IntegratorMC J(G);
  for (int i=0; i<10000; ++i) {  
    int N=1000;
    double value =0.;
    double error =0.;
    J.ImportanceSampling(N, value, error, P, PI);
    //cout << N << endl;
    //cout << "Valor: " << value << endl;
    //cout << "Erro: " << error << endl;
    H2.Fill(value);
  }

  // Acceptance-rejection method

  // Tenho de mudar os limites da função, para não ter valores negativos
  TF1 *H = new TF1 ("H", f, -2.5, 2.5, 0);
  H->SetNpx (1000);
  H->GetXaxis()->SetName("x");
  // Neste caso, o valor real do integral é 5.455009585598826 

  TH1F* H3 = new TH1F ("H3", "AcceptReject;XAxis;YAxis", 1000, 4., 7.);
  H3->SetTitle("Histogram title;An other X title Axis");
  int N1 = 1000; // O AcceptanceRejection não altera o valor de N1
  IntegratorMC K(H);
  for (int i=0; i<20000; ++i) {
    double value = 0.;
    double error = 0.;
    K.AcceptanceRejection (N1, value, error);
    H3->Fill(value);
  }

  // Acceptance-rejection with auxiliary function method: não testei porque necessita de funções particulares e de se determinar q e p
  
  // Escrever tudo em TCanvas e depois em TFile

  //TApplication A("A",0,0);
  TCanvas c1("c1","SimpleIntegration", 0, 0, 600,600);
  H1.SetLineColor(38);
  H1.SetLineWidth(4);  
  H1.Draw("SimpleIntegration");
  c1.Update();
  //A.Run();

  TCanvas c2("c2","ImportanceSampling", 0, 0, 600,600);
  H2.SetLineColor(38);
  H2.SetLineWidth(4);  
  H2.Draw("ImportanceSampling");
  c2.Update();

  //TApplication A("A",0,0);
  TCanvas c3("c3","AcceptReject", 0, 0, 600,600);
  H3->SetLineColor(38);
  H3->SetLineWidth(4);
  H3->GetXaxis()->SetTitle("X axis title"); 
  H3->Draw("AcceptReject");
  c3.Update();
  //A.Run();

  
  // Escrever gráficos num ficheiro
  TFile* file = new TFile("Teste_DerivativeIntegrator", "RECREATE");
  c1.Write();
  c2.Write();
  c3.Write();
  file->Close();

  cout << "\nOs histogramas foram escritos num TFile." << endl;

  // Função RandomGen

  cout << "\nTeste da função RandomGen:" << endl;
  vector<double> vec = IntegratorMC::RandomGen (10, PI);
  for (int i=0; i<vec.size(); i++)
    cout << vec[i] << endl;


  cout << "\n-Teste da Three-Point Formula em Derivator.C-" << endl;

  vector<double> x ({-1., 0., 1., 2., 3., 4., 5.});
  vector<double> y ({-1., 0., 1., 2., 3., 4., 5.});
  int index = 5;
  
  double threepointvalue=0.;
  Derivator::FirstDer_3PointFormula (x, y, index, threepointvalue);

  cout << "Valor da derivada de y=x: " << threepointvalue << endl;

  vector<double> z1({-1., -0.75, -0.5, -0.25, 0., 0.25, 0.5, 1.});
  vector<double> z({cos(-1.), cos(-0.75), cos(-0.5), cos(-0.25), cos(0.), cos(0.25), cos(0.5), cos(1.)});

  Derivator::FirstDer_3PointFormula (z1, z, index, threepointvalue);
  cout << "Valor da derivada de y=cos(x) em x=0.25 rad: " << threepointvalue << endl;

  cout << "\n-Teste de Derivative com Cubic Spline-" << endl;

  double xi[6] = {0., 0.5, 1., 1.5, 2., 2.5};
  double yi[6] = {0., sin(0.5), sin(1.), sin(1.5), sin(2.), sin(2.5)};
  
  Spline3Interpolator spline(6, xi, yi);

  cout << "Valor da primeira derivada de uma função teste em x=2.: " << spline.InterpolateFirstDerivative (2.) << endl;
  cout << "Valor da segunda derivada de uma função teste em x=2.: " << spline.InterpolateSecondDerivative (2.) << endl;

  Spline3Interpolator spline2(8, z1.data(), z.data());

  cout << "Valor da primeira derivada de cos(x) em x=0.: " << spline2.InterpolateFirstDerivative (0.) << endl;
  cout << "Valor da segunda derivada de cos(x) em x=0.: " << spline2.InterpolateSecondDerivative (0.) << endl;

  cout << endl;
  

  return 0;  
}
