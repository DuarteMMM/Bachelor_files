#include "ODEPoint.h"
#include "ODESolver.h"

#include "TH1.h"
#include "TGraph.h"
#include "TCanvas.h"

int main() {

  cout << "\n-=-=-=- Exercício 1b -=-=-=-" << endl;

  // Constantes
  double g = 9.8;
  double l = 5;

  /* Para resolver este exercício, utilizou-se o tempo caraterístico, t_c = sqrt(l/g); fazendo a mudança de variável tau = t/t_c, obtém-se a equação:
     d²theta/dtau² + sin(theta) = 0

     Ficando o sistema:

     -> dx_1/dt = x2 = f1(t, x1, x2)
     -> dx_2/dt = -sin(x1) = f2(t, x1, x2)
  */
  
  
  // Definir as funções
  // Variáveis no array double *x: x[0]: tempo; x[1]: x1; x[2]: x2

  double xmin = 0.;
  double xmax = 150.; // Para haver pelo menos 10 períodos (foi verificado graficamente)
  
  // Função f1
  TF1 f1 ("f1", [&](double* x, double* par){return x[2];}, xmin, xmax, 0);
  
  // Função f2
  TF1 f2 ("f2", [&](double* x, double* par){return -sin(x[1]);}, xmin, xmax, 0);

  // Runge-Kutta de ordem 4
  double step = 0.01;
  double time = xmax - xmin;

  double theta_0_inicial = (65.*M_PI)/180.; // Em radianos

  ODEPoint initial_conditions (0, vector<double> ({theta_0_inicial, 0.}), 2);
  ODESolver solver (initial_conditions, vector<TF1>({f1, f2}));
  vector<ODEPoint> solution = solver.RK4Solve (step, time);

  // Vetores e valores com tempo, theta, derivada de theta e energia, respetivamente
  vector<double> time_vec;
  vector<double> theta_vec; 
  vector<double> theta_der_vec;
  vector<double> energy_vec;

  double time_value;
  double theta_value;
  double theta_der_value;
  double energy_value;

  // Ciclo dos valores necessários a obter
  
  for(int i = 0; i < solution.size(); i++) {

    // Tempo
    time_value = solution[i].getIndepVar();
    time_vec.push_back (time_value);

    // Theta
    theta_value = solution[i].getDepVar(0);
    theta_vec.push_back (theta_value);
    
    // Theta's derivative with respect to time
    theta_der_value = solution[i].getDepVar(1);
    theta_der_vec.push_back (theta_der_value);

    // Energy
    // Fórmula da energia total: E = Ep + Ec = mgl(1-cos(theta)) + 0.5*m*v²; considerou-se m=1, visto que a energia total não dependerá da massa
    energy_value = g*l*(1.-cos(theta_value)) + 0.5*theta_der_value*theta_der_value*l*l;
    energy_vec.push_back (energy_value);
    
  }
  

  //  Criar ficheiro pdf com plot de theta em função de theta_0
  cout << "\nGuardar gráfico em 'prob1b_diagramafase.pdf':" << endl;
  TGraph graph1 (theta_vec.size(), theta_der_vec.data(), theta_vec.data());
  TCanvas canvas1 ("Fase","Fase");
  graph1.SetMarkerColor(38);
  graph1.SetMarkerStyle(kFullDotMedium);
  graph1.SetTitle ("Phase diagram");
  graph1.GetHistogram()->GetXaxis()->SetTitle("theta_der (radians per seconds)");
  graph1.GetHistogram()->GetYaxis()->SetTitle("theta (radians)");
  graph1.Draw("AC");
  canvas1.Update();
  canvas1.SaveAs("prob1b_diagramafase.pdf");

  //  Criar ficheiro pdf com plot da energia em função de t
  cout << "\nGuardar gráfico em 'prob1b_energia.pdf':" << endl;
  TGraph graph2 (time_vec.size(), time_vec.data(), energy_vec.data());
  TCanvas canvas2 ("Energy","Energy");
  graph2.SetMarkerColor(38);
  graph2.SetMarkerStyle(kFullDotMedium);
  graph2.SetTitle ("Energy over time");
  graph2.GetHistogram()->GetXaxis()->SetTitle("t(s)");
  graph2.GetHistogram()->GetYaxis()->SetTitle("E(J)");
  graph2.Draw("AC");
  canvas2.Update();
  canvas2.SaveAs("prob1b_energia.pdf");

  //  Criar ficheiro pdf com plot de theta em função de t
  cout << "\nGuardar gráfico em 'prob1b_theta.pdf':" << endl;
  TGraph graph3 (time_vec.size(), time_vec.data(), theta_vec.data());
  TCanvas canvas3 ("Angle","Angle");
  graph3.SetMarkerColor(38);
  graph3.SetMarkerStyle(kFullDotMedium);
  graph3.SetTitle ("Angle over time");
  graph3.GetHistogram()->GetXaxis()->SetTitle("t(s)");
  graph3.GetHistogram()->GetYaxis()->SetTitle("theta (radians)");
  graph3.Draw("AC");
  canvas3.Update();
  canvas3.SaveAs("prob1b_theta.pdf");

  // Terminar o programa
  cout << "\n-Fim da resolução do exercício 1b-\n" << endl;
  return 0;

  /* Nota: Verificou-se que o gráfico da energia em função do tempo não corresponde ao esperado, visto que se esperaria ter a energia constante ao longo do tempo; pensa-se que o resultado obtido ter-se-á devido à necessidade de considerar unidades reduzidas no cálculo da energia */
  
}
