#include "DataReader.h"
#include "DataManip.h"
#include <iostream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TFrame.h"

using namespace std;

void mtrab01 (){

  DataManip D("../SunspotNumberDATA2020.txt");

  //TGraph* grafico = D.GetDataGraph(),* grafico2 = D.GetDataDerivativeGraph();
  TGraph* grafico = D.GetMovingAverageGraph (11, "g11");
  
  //TH1D* histograma = D.GetDataDerivativeHisto();
  TCanvas* canvas = new TCanvas("c1", "Sunspot Data", 20, 10, 500, 700);
  TH1F* cr = canvas->DrawFrame(1849,-1000,1850,1000);
  cr->SetXTitle("Time (years)");
  cr->SetYTitle("Sunspot Number");
  
  canvas->SetFillColor(kBlue-8);
  canvas->SetGrid();

  //grafico->Print();
  
  //cout << grafico->GetMarkerStyle() << endl;
  //cout << grafico->GetMarkerColor() << endl;

  grafico->Draw("L");
  canvas->Modified();
  canvas->WaitPrimitive();
  /*
  //grafico2->Print();
  TH1F* cr2 = canvas->DrawFrame(1849,-5000,1850,5000);
  cr2->SetXTitle("Time (years)");
  cr2->SetYTitle("Sunspot Number");
  canvas->SetFillColor(kBlue-8);
  canvas->SetGrid();
  
  grafico2->Draw("P");
  canvas->Modified();
  canvas->WaitPrimitive();
  
  histograma->SetFillColor(kRed);
  histograma->SetMarkerStyle(20);
  histograma->SetLineWidth(3);
  histograma->SetMarkerColor(kRed-2);
  
  histograma->DrawCopy();
  canvas->Modified();
  canvas->WaitPrimitive();*/


}
