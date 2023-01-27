#include <iostream> // cout,...
#include "TRandom3.h" // Values in [0,1]
#include <vector> // vector<double>

#include "TCanvas.h"
#include "TH1.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"


using namespace std;

int main () {

  cout << "\n-Problema 1-\n" << endl;

  double dt = 1; // Em dias
  int number_iter=0;
  
  double tau_Bi = 7.5;
  double lambda_Bi = 1./tau_Bi;

  double tau_Po = 200;
  double lambda_Po = 1./tau_Po;

  double random;
  TRandom3* gRandom = new TRandom3();
  gRandom->SetSeed(0);

  int Bi_number = 500;
  int Po_number = 0;
  int Pb_number = 0;
  
  int somar_a_Po = 0;
  int somar_a_Pb = 0;

  vector<double> Bi_vector;
  vector<double> Po_vector;
  vector<double> Pb_vector;
  vector<double> time_vector;

  // Valores iniciais
  Bi_vector.push_back(Bi_number);
  Po_vector.push_back(Po_number);
  Pb_vector.push_back(Pb_number);
  time_vector.push_back (0);
  
  while (Bi_number>0) {

    number_iter++;
    somar_a_Po=0;
    somar_a_Pb=0;
    
    random = gRandom->Uniform(); // Generate random between 0 and 1

    if (random < lambda_Bi*dt && Bi_number > 0) {
      Bi_number -= 1;
      somar_a_Po = 1;
    }

    Po_number += somar_a_Po;
    
    if (Po_number > 0 && random < lambda_Po*dt) {
      Po_number -= 1;
      somar_a_Pb = 1;
    }

    Pb_number += somar_a_Pb;

    Bi_vector.push_back (Bi_number);
    Po_vector.push_back(Po_number);
    Pb_vector.push_back(Pb_number);

    time_vector.push_back(dt*number_iter);
  }

  double time_max = dt*number_iter;

  number_iter++; // Para ficar igual ao número de elementos nos vetores

  cout << "Alínea a" << endl;
  
  TCanvas canvas ("Radioactive_decay", "Radioactive_decay");
  
  TGraph *graph = new TGraph (number_iter, time_vector.data(), Bi_vector.data());
  graph->SetMarkerColor(kBlue+1);
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(0.5);
  
  TGraph *graph2 = new TGraph (number_iter, time_vector.data(), Po_vector.data());
  graph2->SetMarkerColor(kRed+1);
  graph2->SetMarkerSize(0.5);
  graph2->SetMarkerStyle(20);

  TGraph *graph3 = new TGraph (number_iter, time_vector.data(), Pb_vector.data());
  graph3->SetMarkerColor(kGreen+1);
  graph3->SetMarkerSize(0.5);
  graph3->SetMarkerStyle(20);

  TMultiGraph *multi = new TMultiGraph();

  multi->Add(graph);
  multi->Add(graph2);
  multi->Add(graph3);
  multi->Draw("AP");
  multi->SetTitle ("Radioactive decay");
  multi->GetHistogram()->GetXaxis()->SetTitle("t (days)");
  multi->GetHistogram()->GetYaxis()->SetTitle("N");

  canvas.Modified();
  canvas.Update();

  canvas.SaveAs("prob1a.pdf");
  
  cout << "\nAlínea b\n-> Número de isótopos de Po em t=180 dias: " << Po_vector[180] << endl << endl;

  delete graph;
  delete graph2;
  delete graph3;
  delete multi;
  delete gRandom;
  
  return 0;

}
