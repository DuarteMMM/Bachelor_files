#include "Integrator.h"
#include "IntegratorMC.h"

#include "TH1.h"
#include "TGraph.h"
#include "TCanvas.h"

//#include <cmath> // sqrt, M_PI

//#include <iostream>

int main() {

  cout << "\n-=-=-=- Exercício 1a -=-=-=-" << endl;

  // Variáveis
  double l = 5;
  double g = 9.8;
  double theta0_graus = 1.;
  double theta0 = (M_PI*theta0_graus) / 180.; // Valor inicial (em radianos)

  // Limites do integral
  double xlow = 0.; 
  double xup = M_PI/2.;


  double periodo = 0.;

  // Cálculo dos integrais
  //IntegratorMC I(G);

  int N = 1000;
  double error = 1.e-3; // Precisão relativa pretendida
  double value = 0.; // Variável com valor do integral
  
  double real = 0.; // Valor verdadeiro do integral (para testar)

  // Vetores para desenho do gráfico
  double* theta0_array = new double [23];
  double* periodo_array = new double [23];

  cout << "\nFoi usado o método SimpleIntegration para cálculo dos integrais.\n" << endl;
  
  // Ciclo
  for (int n=0; n<23; n++) {

    // Função
    auto f = [theta0](double *x, double *par=nullptr)
	     {
	       return 1 / sqrt (1 - sin(theta0/2.)*sin(theta0/2.)*sin(x[0])*sin(x[0]));
	     };
    
    TF1 *G = new TF1 ("Function to integrate", f, xlow, xup, 0); // npar=0, ndim=1 (default)

    IntegratorMC I(G);
    
    // Guardar valor de theta0
    theta0_array[n] = theta0_graus;
    
    // Calcular integral
    I.SimpleIntegration (N, value, error);

    //cout << "Número de aleatórios gerados: " << N << endl;
    //cout << "Valor do integral: " << value << endl;
    //cout << "Erro relativo: " << error << endl;
    //real = G.Integral (xlow, xup);
    //cout << "Valor verdadeiro do integral: " << real << endl << endl;

    // Calcular e guardar período
    periodo = 4*sqrt(l/g)*value;
    periodo_array[n] = periodo;

    cout << "Com theta0 = " << theta0_graus << "º: T = " << periodo << " segundos" << endl;

    value = 0.;
    error = 1.e-3;

    theta0_graus += 4;
    theta0 = (M_PI*theta0_graus) / 180.;
    delete G;
  }

  //  Criar ficheiro pdf com plot desejado
  
  cout << "\nGuardar gráfico em 'prob1a_periodo.pdf':" << endl;
  
  TGraph graph (23, theta0_array, periodo_array);
  TCanvas canvas ("Periodos","Periodos");
  graph.SetMarkerColor(38);
  graph.SetMarkerStyle(kFullDotMedium);
  graph.SetTitle ("Period of pendulum");
  graph.GetHistogram()->GetXaxis()->SetTitle("theta0 (degrees)");
  graph.GetHistogram()->GetYaxis()->SetTitle("T(s)");
  graph.Draw("AC");
  canvas.Update();
  canvas.SaveAs("prob1a_periodo.pdf");


  // Terminar o programa
  cout << "\n-Fim da resolução do exercício 1a-\n" << endl;
  delete periodo_array;
  delete theta0_array;
  
  return 0;
}
