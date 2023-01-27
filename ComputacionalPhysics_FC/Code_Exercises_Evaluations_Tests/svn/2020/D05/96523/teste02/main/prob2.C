#include <vector> // vector<double>
#include <iostream> // cout

#include "TRandom3.h" // randoms in [0,1]

#include "TCanvas.h"
#include "TH1.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"

using namespace std;

int main() {

  cout << "\n-Problema 2-\n" << endl;

  double dt=1.;
  double t = 0.;
  
  vector<double> time;

  double particle1 = 100;
  double particle2 = 100;
  double particle3 = 100;

  vector<double> par1_vec;
  vector<double> par2_vec;
  vector<double> par3_vec;

  vector<double> time_fix_instante_0 (400, 0);
  vector<double> time_fix_instante_500 (400, 500);
  vector<double> instante_0 (400, 100); // Vector com as 400 partículas, todas em 100
  vector<double> instante_500 (400, 100); // Cópia do vetor acima, este o qual será alterado

  par1_vec.push_back(particle1);
  par2_vec.push_back(particle2);
  par3_vec.push_back(particle3);
  

  double random;
  TRandom3* gRandom = new TRandom3();
  gRandom->SetSeed(0);


  time.push_back(t);

  int i = 1;
  int j;
  
  while (i<=500) {

    j = 0;
    
    t = dt*i;
    time.push_back(t);

    while (j<400) {
      random = gRandom->Uniform();
      if (random < 0.5 && instante_500[j] > 0)
	instante_500[j] -= 1;
      if (random >= 0.5 && instante_500[j] < 200)
	instante_500[j] += 1;
      j++;
    }
    

    random = gRandom->Uniform();

    if (random < 0.5 && particle1 > 0)
      particle1 -= 1;
    if (random >= 0.5 && particle1 < 200)
      particle1 += 1;

    par1_vec.push_back (particle1);

    random = gRandom->Uniform();

    if (random < 0.5 && particle2 > 0)
      particle2 -= 1;
    if (random >=0.5 && particle2 < 200)
      particle2 += 1;

    par2_vec.push_back (particle2);

    random = gRandom->Uniform();

    if (random < 0.5 && particle3 > 0)
      particle3 -= 1;
    if (random >= 0.5 && particle3 < 200)
      particle3 += 1;

    par3_vec.push_back (particle3);
    i++;
  }

  cout << "Alínea a" << endl;

  TCanvas canvas0 ("Distributions", "Distributions");
  
  TGraph *graph01 = new TGraph (400, instante_0.data(), time_fix_instante_0.data());
  graph01->SetMarkerColor(kBlue+1);
  graph01->SetMarkerStyle(20);
  graph01->SetMarkerSize(0.5);
  
  TGraph *graph02 = new TGraph (400, instante_500.data(), time_fix_instante_500.data());
  graph02->SetMarkerColor(kRed+1);
  graph02->SetMarkerStyle(20);
  graph02->SetMarkerSize(0.5);

  TMultiGraph *multi0 = new TMultiGraph();

  multi0->Add(graph01);
  multi0->Add(graph02);
  multi0->Draw("AP");
  multi0->SetTitle ("Distributions in t=0 and t=500");
  multi0->GetHistogram()->GetXaxis()->SetTitle("x");
  multi0->GetHistogram()->GetYaxis()->SetTitle("t");

  multi0->GetYaxis()->SetRangeUser (-50, 550); // De forma a centrar as distribuições

  canvas0.Modified();
  canvas0.Update();

  canvas0.SaveAs("prob2a1.pdf");

  
  TCanvas canvas ("Particles", "Particles");
  
  TGraph *graph = new TGraph (501, time.data(), par1_vec.data());
  graph->SetMarkerColor(kBlue+1);
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(0.5);
  
  TGraph *graph2 = new TGraph (501, time.data(), par2_vec.data());
  graph2->SetMarkerColor(kRed+1);
  graph2->SetMarkerStyle(20);
  graph2->SetMarkerSize(0.5);


  TGraph *graph3 = new TGraph (501, time.data(), par3_vec.data());
  graph3->SetMarkerColor(kGreen+1);
  graph3->SetMarkerStyle(20);
  graph3->SetMarkerSize(0.5);

  TMultiGraph *multi = new TMultiGraph();

  multi->Add(graph);
  multi->Add(graph2);
  multi->Add(graph3);
  multi->Draw("AP");
  multi->SetTitle ("Trajectories over time");
  multi->GetHistogram()->GetXaxis()->SetTitle("t");
  multi->GetHistogram()->GetYaxis()->SetTitle("x");

  canvas.Modified();
  canvas.Update();

  canvas.SaveAs("prob2a2.pdf");

  bool left_side = false;
  bool right_side = false;

  double current_time = 500;
  int cont = 0;

  while (!left_side && !right_side) {

    j=0;
    cont++;
    
    current_time += dt*cont;

    while (j<400) {
      
      random = gRandom->Uniform();
      if (random < 0.5)
	instante_500[j] -= 1;
      if (random >= 0.5)
	instante_500[j] += 1;

      if (abs(instante_500[j]-50.) < 0.5)
	left_side = true;
      if (abs(instante_500[j]-100.) < 0.5)
	right_side = true;
      
      j++;
    }
  }

  cout << "\nAlínea b\nTempo demorado até se espalhar pela chávena: " << current_time << endl;

  TCanvas canvas2 ("Cup", "Cup");
  
  TGraph *graph_cup = new TGraph (400, instante_500.data(), time_fix_instante_500.data());
  graph_cup->SetMarkerColor(kBlue+1);
  graph_cup->SetMarkerStyle(20);
  graph_cup->SetMarkerSize(0.5);
  graph_cup->SetTitle ("Distribution in cup of tea when fully occupied");
  graph_cup->GetHistogram()->GetXaxis()->SetTitle("x");
  graph_cup->GetHistogram()->GetYaxis()->SetTitle("t");
  graph_cup->Draw("AP");

  graph_cup->GetXaxis()->SetRangeUser (50, 150);
  graph_cup->GetYaxis()->SetRangeUser (490, 510); // De forma a centrar
  
  canvas2.Modified();
  canvas2.Update();

  canvas2.SaveAs("prob2b.pdf");

  cout << endl;

  delete graph01;
  delete graph02;
  delete multi0;
  delete graph;
  delete graph2;
  delete graph3;
  delete multi;
  delete graph_cup;
  delete gRandom;
  
  return 0;
}
