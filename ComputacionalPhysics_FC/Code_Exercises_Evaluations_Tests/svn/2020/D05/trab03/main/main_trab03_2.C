#include <cstdio>
#include <iomanip>

#include "TCanvas.h"
#include "TH1.h"
#include "TRandom.h"
#include "TGraph.h"

#include "ODESolver.h"

#define EPSILON_K 120

using namespace std;

// Recebe vetor com as posições x das partículas seguidas das posições y das particulas
void CalculatePotentialEnergy (double& EnergiaPotencial, vector<double> r, int N, double epsilon, double sigma) {

  double value; // Soma de quadrados
  double dis;
  double sum=0.;
  for (int i=0; i<N-1; i++) {
    for (int j=i+1; j<N; j++) {
      value = (r[i]-r[j])*(r[i]-r[j]) + (r[i+N]-r[j+N])*(r[i+N]-r[j+N]); // r² para par de partículas
      EnergiaPotencial += (pow(sigma, 6) / pow(value, 6) - 1 / pow(value, 3)); // Somar à energia potencial as potências
    }
  }
  EnergiaPotencial *= 4*epsilon*pow(sigma,6);
}

// Recebe vetor v com 100 velocidades x seguidas de 100 velocidades y
void CalculateKineticEnergy (double& EnergiaCinetica, double m, vector<double> v) {
  for_each ( v.begin(), v.end(), [&EnergiaCinetica, m] (double x) {EnergiaCinetica += 0.5*m*x*x;});
}

// Energia total = Energia cinética + Energia potencial
double CalculateTotalEnergy (double EnergiaCinetica, double EnergiaPotencial) {
  return EnergiaCinetica+EnergiaPotencial;
}

// Variação relativa da energia
double CalculateVarEnergia (double Energia_total, double Energia_inicial) {
  return (Energia_total-Energia_inicial)/(Energia_inicial);
}

// É preciso guardar em algum lado um vetor com as posições iniciais todas
void CalculateDesvioQuadMedio (double& Desvio, vector<double> r, vector<double> r0, int N) {
  
  // Diferença entre os elementos do vetor e guardados em r.begin()
  transform (r.begin(), r.end(), r0.begin(), r.begin(), minus<double>());

  // Somar os quadrados das diferenças
  for_each (r.begin(), r.end(), [&Desvio](double x) {Desvio += x*x;});

  Desvio = Desvio/N; // Valor médio
}

double CalculateTemperature (double EnergiaCinetica, int N) {
  return EnergiaCinetica/N*EPSILON_K;
}


vector<double> CalculateFirstStepPositions(int num_particles, double time_step, vector<double>initialpositions, vector<double> initialvelocities, vector<TF1> accel_equations) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  vector<double> result(num_particles*2, 0.);
    
  for(int i = 0; i < num_particles; i++) {

    double i_double = (double) i;

    double accel_x = accel_equations[0].EvalPar(&initialpositions[0], &i_double);
    double accel_y = accel_equations[1].EvalPar(&initialpositions[0], &i_double);
      
    result[i] = initialpositions[i] + time_step * (initialvelocities[i] + time_step/2 * accel_x);
    result[i+num_particles] = initialpositions[i+num_particles] + time_step * (initialvelocities[i+num_particles] + time_step/2 * accel_y);
    
  }

  return result;
}


vector<double> CreateInitialPositions(int halfsize, double d) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  vector<double> initialpositions (halfsize*2, 0.);

  for (int i = 0; i < halfsize; i++) {

    initialpositions[i] = 6 + d * (i%10);
    initialpositions[i+halfsize] = 6 + d * (int)(i/10);

  }
  
  return initialpositions;
}


vector<double> CreateInitialVelocities(int halfsize, double velocity_mag) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  vector<double> initialvelocities (halfsize*2, 0.);

  if (velocity_mag == 0.) {

    fill(initialvelocities.begin(), initialvelocities.end(), 0.);

  }
  
  gRandom->SetSeed(0);

  for (int i = 0; i < halfsize; i++) {

    double theta = gRandom->Uniform() * 2 * M_PI;
    
    initialvelocities[i] = cos(theta) * velocity_mag;
    initialvelocities[i+halfsize] = sin(theta) * velocity_mag;

  }

  return initialvelocities;
}


void CalculateVelocities(double time_step, int size, vector<double> positions_next, vector<double> positions_previous, vector<double>& velocities) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  for(int i = 0; i < size; i++) {

    velocities[i] *= (positions_next[i]/(2.*time_step)) - (positions_previous[i]/(2.*time_step));

  }

}


void EnforceBorders (int L, int size, vector<double>& positions, vector<double>& velocities) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  for (int part = 0; part < size; part++) {

    
    if (positions[part] <= 0) {

      positions[part] *= -1.;
      velocities[part] = -1.;

    } else if (positions[part] >= L) {

      positions[part] = 2.*L - positions[part];
      velocities[part] = -1.;

    } else {

      velocities[part] = 1.;

    }

  }
}


int main() {
  
  cout << "\n-=-=-=- Exercício 2 -=-=-=-" << endl;

  ///////////////////// Alínea a

  cout << "\n/////////////// Alínea a" << endl;
  cout << "\n A executar o programa...\n" << endl;
 
  
  double time_step = 1.e-3;
  
  //caracterização do sistema
  int L = 22;
  double m = 1.;
  int N = 100;
  int N2 = 2*N;
  double dist = 1.;
  double v0 = 0;
  double time = 50.;

  /* Unidades:
     - distâncias/comprimentos em sigmas
     - energia em epsilons
     - força em 'epsilon/sigma's
     - massa em massas atómicas de árgon
     - tempo em sigma*sqrt(massa atómica de árgon/epsilon)
  */

  
  auto accel_x = [m, N](double *x, double *par) {
		   double result = 0.;
		   for (int i = 0; i < N; i++) {

		     if (i != par[0]) {
		       double d_x = x[i] - x[(int) par[0]];
		       double d_y = x[i+N] - x[((int) par[0])+N];
		       double r_2 = d_x*d_x + d_y*d_y;
		       result += -1./m * 4/r_2 * (12 * pow(r_2,-6) - 6 * pow(r_2, -3)) * d_x;

		     }

		   }

		   return result;
		 };

  //current é um parâmetro
  auto accel_y = [m, N](double *x, double *par) {
		   double result = 0.;
		   for (int i = 0; i < N; i++) {

		     if (i != par[0]) {
		       double d_x = x[i] - x[(int) par[0]];
		       double d_y = x[i+N] - x[((int) par[0])+N];
		       double r_2 = d_x*d_x + d_y*d_y;
		       result += -1./m * 4/r_2 * (12 * pow(r_2,-6) - 6 * pow(r_2, -3)) * d_y;
		     }

		   }

		   return result;
		 };

  TF1 tf1_accel_x ("accel_x", accel_x, 0, time, 1);
  TF1 tf1_accel_y ("accel_y", accel_y, 0, time, 1);

  //TF1 tf1_accel ("accel", accel, 0, time, 1);
  
  //definição das funções
  vector<TF1> functions = {tf1_accel_x, tf1_accel_y};
  //vector<TF1> functions [1] = {tf1_accel};

#ifdef DEBUG
  cout << "Definiu as funções." << endl;
#endif
  
  //definição de condições iniciais
  
  vector<double> initialpositions = CreateInitialPositions(N, dist);
  vector<double> initialvelocities = CreateInitialVelocities(N, v0);

#ifdef DEBUG
  cout << "Definiu condições iniciais" << endl;
#endif
  
  //cálculo das coordenadas do sistema após um step

  vector<double> firststeppositions = CalculateFirstStepPositions(N, time_step, initialpositions, initialvelocities, functions);
  vector<double> firststepvelocities(N2);
  fill(firststepvelocities.begin(), firststepvelocities.end(), 1);

#ifdef DEBUG
  cout << "Calculou após 1 step" << endl;
#endif
  
  EnforceBorders(L, N2, firststeppositions, firststepvelocities);
#ifdef DEBUG
  cout << "Viu condições fronteira para 1 step" << endl;
#endif
  
  //loop de cálculo automático (para restantes steps)
  ODEPoint initialpoint (0., initialpositions, N2);
  ODESolver SystemSolver(initialpoint,functions);
  
  int steps = (int) (time/time_step);
  
#ifdef DEBUG
  cout << steps << endl;
#endif

  // Vectors com variáveis a serem calculadas
  vector<vector<double>> positions(steps);
  vector<vector<double>> velocities(steps, vector<double>(N2, 1.));
  vector<double> potentialenergy(steps, 0.);
  vector<double> kineticenergy(steps, 0.);
  vector<double> totalenergy(steps, 0.);
  vector<double> time_vector(steps);
  vector<double> temperatures_vector(steps);
  vector<double> var_energia_vector(steps);
  vector<double> desvio_quad_med(steps);

  // Instante(s) inicial(ais)
  positions[0] = initialpositions;
  positions[1] = firststeppositions;
  CalculateDesvioQuadMedio (desvio_quad_med[0], positions[0], positions[0], N);
  CalculateDesvioQuadMedio (desvio_quad_med[1], positions[1], positions[0], N);
  velocities[0] = initialvelocities;
  CalculatePotentialEnergy(potentialenergy[0], positions[0], N, 1., 1.);
  CalculatePotentialEnergy(potentialenergy[1], positions[1], N, 1., 1.);
  CalculateKineticEnergy(kineticenergy[0], m, velocities[0]);
  temperatures_vector[0] = CalculateTemperature (kineticenergy[0], N);
  totalenergy[0] = CalculateTotalEnergy(kineticenergy[0], potentialenergy[0]);
  var_energia_vector[0] = CalculateVarEnergia (totalenergy[0], totalenergy[0]);
  time_vector[0] = 0.;
  time_vector[1] = time_step;
  
  for (int t = 2; t < steps; t++) {

    positions[t] = SystemSolver.LoopVerletIterate(time_step, N, positions[t-2], positions[t-1]);
    
#ifdef DEBUG
    cout << "Calculou positions[t]!" << endl;
#endif
    
    EnforceBorders(L, N2, positions[t], velocities[t]);
    
#ifdef DEBUG
    cout << "Verificou condições fronteira!" << endl;
#endif
    
    CalculateVelocities(time_step, N2, positions[t], positions[t-2], velocities[t-1]);
    
#ifdef DEBUG
    cout << "Calculou velocidades!" << endl;
#endif

    CalculatePotentialEnergy(potentialenergy[t], positions[t], N, 1., 1.);
    CalculateKineticEnergy(kineticenergy[t-1], m, velocities[t-1]);
    temperatures_vector[t-1] = CalculateTemperature (kineticenergy[t-1], N);
    totalenergy[t-1] = CalculateTotalEnergy(kineticenergy[t-1], potentialenergy[t-1]);
    var_energia_vector[t-1] = CalculateVarEnergia (totalenergy[t-1], totalenergy[0]);
    time_vector[t] = t * time_step;
    CalculateDesvioQuadMedio (desvio_quad_med[t], positions[t], positions[0], N);

  }

#ifdef DEBUG
  cout << "Saiu do loop" << endl;
#endif
  
  CalculateVelocities(time_step, N2, SystemSolver.LoopVerletIterate(time_step, N, positions[steps-2], positions[steps-1]), positions[steps-2], velocities[steps-1]);
  CalculateKineticEnergy(kineticenergy[steps-1], m, velocities[steps-1]);
  temperatures_vector[steps-1] = CalculateTemperature (kineticenergy[steps-1], N);
  totalenergy[steps-1] = CalculateTotalEnergy(kineticenergy[steps-1], potentialenergy[steps-1]);
  var_energia_vector[0] = CalculateVarEnergia (totalenergy[steps-1], totalenergy[0]);
  

  // Prints a fazer no ecrã


  ////////// Alínea a
  
  // Escrita de valores no terminal

  
  // Avaliar chegada ao equilíbrio
  int eq;
  double t_eq;
  for(int i = steps-2; i >= 0; i--) {

    if (abs(temperatures_vector[i] - temperatures_vector[steps-1]) < 0.001) {

      eq = i;
    
    }
    
  }

  t_eq = time_vector[eq];

  // Escrita de valores no terminal
  cout << "Tempo estimado para que o sistema atinja o equilíbrio: " << t_eq << endl;
  cout << "Temperatura do sistema em equilíbrio: " << temperatures_vector[eq] << " K\n" << endl;

  //  Criar ficheiro pdf com plot das posições em equilíbrio

  // Dividir o vetor das posições em 2: posições x + posições y
  vector<double> x_equilibrio (positions[eq].begin(), positions[eq].begin()+N);
  vector<double> y_equilibrio (positions[eq].begin()+N, positions[eq].end());

  TGraph graph_x_y_eq  (N, x_equilibrio.data(), y_equilibrio.data()); // Número de pontos, vetores
  TCanvas c_x_y_eq ("c_x_y_eq","c_x_y_eq");
  graph_x_y_eq.SetMarkerColor(kBlue);
  graph_x_y_eq.SetMarkerStyle(kFullCircle);
  graph_x_y_eq.SetTitle ("Particles' positions in equilibrium");
  graph_x_y_eq.GetHistogram()->GetXaxis()->SetTitle("x");
  graph_x_y_eq.GetHistogram()->GetYaxis()->SetTitle("y");
  graph_x_y_eq.GetXaxis()->SetLimits(0., 22.);
  graph_x_y_eq.GetYaxis()->SetRangeUser(0., 22.);
  graph_x_y_eq.Draw("AP");
  c_x_y_eq.Update();
  c_x_y_eq.SaveAs("trab03_2a_sistema.pdf");

  
  //  Criar ficheiro pdf com plot da energia total do sistema ao longo do tempo e da sua varição relativ

  TGraph graph_energia  (steps, time_vector.data(), totalenergy.data());
  TCanvas c_energia ("c_energia","c_energia");
  graph_energia.SetMarkerColor(38);
  graph_energia.SetMarkerStyle(kFullDotMedium);
  graph_energia.SetTitle ("Total energy of the system");
  graph_energia.GetHistogram()->GetXaxis()->SetTitle("t");
  graph_energia.GetHistogram()->GetYaxis()->SetTitle("E");
  graph_energia.Draw("AP");
  c_energia.Update();
  c_energia.Print("trab03_2a_energiatotal.pdf(","Title:Page 1"); // Abrir o ficheiro
  
  
  TGraph graph_var_energia (steps, time_vector.data(), var_energia_vector.data());
  TCanvas c_var_energia ("c_var_energia","c_var_energia");
  graph_var_energia.SetMarkerColor(46);
  graph_var_energia.SetMarkerStyle(kFullDotSmall);
  graph_var_energia.SetTitle ("Relative Energy Variation");
  graph_var_energia.GetHistogram()->GetXaxis()->SetTitle("t");
  graph_var_energia.GetHistogram()->GetYaxis()->SetTitle("#frac{E(t)-E(0)}{E(0)}");
  graph_var_energia.Draw("AP");
  c_var_energia.Update();
  c_var_energia.Print("trab03_2a_energiatotal.pdf)","Title:Page 2"); // Fechar o ficheiro
  

  
  //  Criar ficheiro pdf com plot da temperatura do sistema ao longo do tempo

  TGraph graph_temp (steps, time_vector.data(), temperatures_vector.data());
  TCanvas c_temp ("c_temp","c_temp");
  graph_temp.SetMarkerColor(kRed);
  graph_temp.SetMarkerStyle(kFullDotMedium);
  graph_temp.SetTitle ("Temperature (average kinetic energy)");
  graph_temp.GetHistogram()->GetXaxis()->SetTitle("t");
  graph_temp.GetHistogram()->GetYaxis()->SetTitle("T");
  graph_temp.Draw("AP");
  c_temp.Update();
  c_temp.SaveAs("trab03_2a_temperatura.pdf");

  
  //  Criar ficheiro pdf com plot do desvio quadrático médio ao longo do tempo

  TGraph graph_desvio (steps, time_vector.data(), desvio_quad_med.data());
  TCanvas c_desvio ("c_desvio","c_desvio");
  graph_desvio.SetMarkerColor(38);
  graph_desvio.SetMarkerStyle(kFullDotMedium);
  graph_desvio.SetTitle ("Deviation");
  graph_desvio.GetHistogram()->GetXaxis()->SetTitle("t");
  graph_desvio.GetHistogram()->GetYaxis()->SetTitle("<r^{2}>");
  graph_desvio.Draw("AP");
  c_desvio.Update();
  c_desvio.SaveAs("trab03_2a_desvioquadratico.pdf");


  ///////////////////// Alínea b

  cout << "\n/////////////// Alínea b\n" << endl;

  
  // Definir a função MB (multiplicada pelo número de partículas, N, por se tratar de uma função densidade de prob.)

  double mass = 1.; // Massa de um átomo de Ar em unidades reduzidas
  double k = 1./120.; // Constante de Boltzmann em unidades reduzidas
  double T = temperatures_vector[steps-1]; // Temperatura de equilíbrio
  
  auto f = [mass, k, T, N](double *x, double *par=nullptr)
  	   {
  	     return N*4*M_PI * pow(mass/(2*M_PI*k*T), 1.5) * x[0] * x[0] * exp (-0.5* ( (mass*x[0]*x[0]) / (k*T) ));
	   };

  double xup = 20.;
  
  TF1 G ("Maxwell-Boltzmann", f, -xup, xup, 0);


  //  Criar ficheiro pdf com plot das duas distribuições sobrepostas

  TH1F H("H", "Velocities (blue) vs. MB (red)", 1000, -xup, xup);
  for (int i=0; i<N; ++i) 
    H.Fill(sqrt(velocities[steps-1][i]*velocities[steps-1][i] + velocities[steps-1][i+N]*velocities[steps-1][i+N]));
  TCanvas c_MB("c_MB","c_MB");
  H.SetLineColor(kBlue+1);
  H.SetLineWidth(4);
  H.GetXaxis()->SetTitle("v");
  H.Draw("HIST");
  G.SetLineColor(kRed+1);
  G.SetLineWidth(4);
  G.Draw("SAME");
  c_MB.Update();
  c_MB.SaveAs("trab03_2b_MB.pdf");

  
  // Terminar o programa
  cout << "\n-Fim da resolução do exercício 2-\n" << endl;
  
  return 0;
}

