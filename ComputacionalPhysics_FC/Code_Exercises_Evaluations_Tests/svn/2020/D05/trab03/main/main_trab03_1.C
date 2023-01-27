#include "Integrator.h"
#include "IntegratorMC.h"

#include "TH1.h"
#include "TCanvas.h"

#include <math.h> // M_PI, atan
#include <iostream> // cout

int main() {

  cout << "\n-=-=-=- Exercício 1 -=-=-=-" << endl;

  cout << "\nNota: o exercício foi resolvido tendo em conta moléculas diatómicas (H2)" << endl;

  ///////////////////// Alínea a

  cout << "\n/////////////// Alínea a" << endl;
  
  // Definir a função

  // Massa molar considerada para H: M = 1.00794 g/mol
  double m = 3.34752e-27; // Massa de uma molécula de H2
  double k = 1.380649e-23; // Constante de Boltzmann
  double T = 300; // Temperatura
  
  auto f = [m, k, T](double *x, double *par=nullptr)
  	   {
  	     return 4*M_PI * pow(m/(2*M_PI*k*T), 1.5) * x[0] * x[0] * exp (-0.5* ( (m*x[0]*x[0]) / (k*T) ));
	   };

  /* Analisando a expressão f(v), facilmente se depreende que a mesma tende rapidamente para zero com x -> +inf; ao observar o gráfico guardado no ficheiro "trab03_1a.pdf", verifica-se que os valores da função apresentam valores já pouco significativos para x>7000.; desta forma, definiu-se xup=7000. como limite superior dos integrais, de forma a obter uma boa estimativa do integral impróprio em causa */

  double xup = 7000.;

  TF1 *G = new TF1 ("Maxwell-Boltzmann", f, 0., xup, 0); // npar=0, ndim=1 (default)
  

  // Criar ficheiro pdf com plot da função MB
  cout << "\n->Guardar plot da função de MB em 'trab03_1a.pdf':" << endl;
  TCanvas *c1 = new TCanvas("c1","c1");
  G->SetNpx(10000);
  G->SetLineColor(38);
  G->SetLineWidth(4);
  G->GetHistogram()->GetXaxis()->SetTitle("v");
  G->GetHistogram()->GetYaxis()->SetTitle("f(v)");
  G->Draw();
  c1->SaveAs("trab03_1a.pdf");
  

  // Calcular integral com o método de Romberg

  // O valor teórico do integral impróprio do enunciado é 1, pois f(v) é uma função densidade de probabilidade
  
  cout << "\n->Integral de Romberg" << endl;
  
  Integrator romberg (G, 0., xup);

  double error = 1.e-3; // Erro relativo pretendido
  double value = 0.; // Variável com o valor do integral
  
  int steps = 0;
  int level = 0;
  
  romberg.Romberg(steps,level,value,error);

  cout << "Steps: " << steps << ", Level: " << level << endl;
  cout << "Valor do Integral: " << value << endl;
  cout << "Erro relativo: " <<  error << endl;
  //cout << "Erro absoluto (estimado): " << error * value << endl;
  

  
  // Calcular integral com método de MC - SimpleIntegration

  cout << "\n->Integral MC" << endl;
    
  IntegratorMC I(G);
  
  int N = 1000;
  error = 1.e-3;
  value = 0.;

  /* Realizou-se o cálculo do integral tanto com o método SimpleIntegration como com o método AcceptanceRejection, e verificou-se que o primeiro requeria um número menor de iterações de forma a chegar ao erro relativo pretendido */

  I.SimpleIntegration (N, value, error);
  cout << "Número de aleatórios gerados: " << N << endl;
  cout << "Valor do integral: " << value << endl;
  cout << "Erro relativo: " << error << endl;

  /* // Com método AcceptanceRejection:
     N = 1000;
     value = 0.;
     error = 1.e-3;
     I.AcceptanceRejection (N, value, error);
     cout << "\nCom AcceptanceRejection Integration:" << endl;
     cout << "Número de iterações: " << N << endl;
     cout << "Valor do integral: " << value << endl;
     cout << "Erro relativo: " << error << endl; */
  

  
  //////////////////////////////// Alínea b
  
  cout << "\n/////////////// Alínea b\n" << endl;

  // Definir a função a integrar, v*f(v)
  
  auto f1 = [m, k, T] (double *x, double *par=nullptr)
	    {
	      return x[0]*(4*M_PI * pow(m/(2*M_PI*k*T), 1.5) * x[0] * x[0] * exp (-0.5* ( (m*x[0]*x[0]) / (k*T) )));
	    };
  
  /* Foi determinado o maximizante da função v*f(v): x=1926.643266 (sendo a respetiva imagem y=0.9250819789).
     Utilizou-se uma função de Cauchy como função auxiliar; não normalizada, esta é da forma p(x) = 1 / (1 + ( (x-a)/s )^2 ), sendo que 'a' está associado à translação e 's' ao scale da função auxiliar; assim, colocou-se a=maximizante, e foi selecionado s=2000., de forma a suavizar a função integranda.
     Calculou-se em seguida o valor k1 para normalizar esta função de Cauchy, e obteve-se a inversa x(y) corresponde ao integral indefinido da função auxiliar normalizada. */

  double s = 2000.;
  double a = 1926.643266;
  double k1 = 1. / (s * (atan ((xup-a)/s) - atan ((0.-a)/s) ) );
  
  TF1 *G2 = new TF1 ("Maxwell-Boltzmann: average velocity", f1, 0., xup, 0); // npar=0, ndim=1 (default)
  

  // Função auxiliar, p(x) (normalizada)
  auto p = [s, a, k1] (double *x, double* par=nullptr) {
	     return k1 / ((1 + ((x[0]-a)/s) * ((x[0]-a)/s) ) );
  	   };

  // Analisando o gráfico e a expressão de v*f(v), conclui-se que a função apresenta valores pouco significativos para x>7000., pelo que se continuará a utilizar xup=7000.
  
  TF1 P ("Auxiliary function", p, 0., xup, 0); // npar=0, ndim=1 (default)
  //P.SetNpx(1000);
  

  // Função x(y)
  auto pi = [s, a, k1, xup] (double* x, double* par=nullptr) {
  	      return s*tan ( x[0] / (k1*s) + atan ( (0.-a)/s ) ) + a;
  	    };
  
  TF1 PI ("Inverse function, x(y)", pi, 0., xup, 0); // napr=0, ndim=1 (default)
  //PI.SetNpx (1000);


  // Salvar plots num ficheiro pdf
  cout << "Guardar plots da função MB multiplicada por v e da função auxiliar em 'trab03_1b.pdf':" << endl;
  TCanvas *c2 = new TCanvas("c2","c2");
  G2->SetNpx(1000);
  G2->SetLineColor(38);
  G2->SetLineWidth(4);
  G2->GetHistogram()->GetXaxis()->SetTitle("v");
  G2->GetHistogram()->GetYaxis()->SetTitle("v f(v)");
  G2->Draw();
  c2->Print("trab03_1b.pdf(","Title:Page 1"); // Abrir o pdf
  
  TCanvas *c3 = new TCanvas("c3","c3");
  P.SetNpx(1000);
  P.SetLineColor(46);
  P.SetLineWidth(4);
  P.GetHistogram()->GetXaxis()->SetTitle("x");
  P.GetHistogram()->GetYaxis()->SetTitle("p(x)");
  P.Draw();
  c3->Print("trab03_1b.pdf)","Title:Page 2"); // Fechar o pdf
  

  // Calcular o integral

  /*
  // O valor "verdadeiro" do integral
  double real1 = G2->Integral(0., xup);
  cout << "Valor real: " << real1 << endl;
  */

  IntegratorMC I1(G2);
  
  N = 1000;
  value = 0.;
  error = 1.e-3; // Erro relativo desejado
  
  I1.ImportanceSampling (N, value, error, P, PI);
  cout << "\nNúmero de aleatórios gerados: " << N << endl;
  cout << "Valor médio da velocidade: " << value << endl;
  cout << "Erro relativo: " << error << endl;
  
  
  
  //////////////////////////////// Alínea c
  
  cout << "\n/////////////// Alínea c\n" << endl;
  
  steps = 10;
  level = 10;
  value = 0.;
  error = 0.;
  double maj = xup;
  double min = 0;
  double v0 = xup/2;
  double calc_error = 0;
  
  romberg.SetXMax(v0);
  
  while (abs(value-0.95) > 1.e-10) {
    
    romberg.Romberg (steps, level, value, error);
    
    if (value < 0.95) {

      min = v0;
      v0 = (maj + min)/2;
      
    } else if (value > 0.95) {

      maj = v0;
      v0 = (maj + min) /2;
      
    }

    romberg.SetXMax(v0);
    calc_error = maj - v0;

    error = 0;
  }
    
  cout << fixed << setprecision(15) << "Valor de v0: " << v0 << endl;
  cout << "Erro relativo de v0: " << calc_error/v0 << endl;


  // Terminar o programa
  cout << "\n-Fim da resolução do exercício 1-\n" << endl;
  delete G;
  delete c1;
  delete G2;
  delete c2;
  delete c3;
  
  return 0;
}

