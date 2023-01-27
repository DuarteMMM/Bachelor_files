#include "Vandermonde.h"
#include "FCmatrixFull.h"
#include "FCmatrixAlgorithms.h"

#include <iostream> // cout

#include "TF1.h"
#include "TMath.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TAxis.h"

#define ALINEA_B_NPONTOS 16

using namespace std;

int main() {

  //alínea a)

  cout << endl << "Alínea a):" << endl << endl << endl;
  
  TFile* file = new TFile("./trab02.root", "RECREATE");
  
  int n_a = 10;

  double x = 0.;
  double y = 1.;

  //TF1* test_TF1 = new TF1("test_TF1", "sin(2*TMath::Pi()*x) + 0.002*cos(100*x)", x, y);
  TF1 test_TF1 ("test_TF1", "sin(2*TMath::Pi()*x) + 0.002*cos(100*x)", x, y);
  
  Vandermonde vand (n_a, x, y, test_TF1); // *test_TF1

  cout << "Coeficientes Polinomiais: " << vand.GetCoefficients() << endl;

  TGraph graphpoints = vand.GetGraphPoints();
  TF1 polyfunc = vand.GetPolyFunc();
  graphpoints.SetName("gPoints");
  polyfunc.SetName("fPoly");
  TCanvas* canvas = new TCanvas("cPoly", "", 0, 0, 1000, 800);

  (graphpoints).Draw("AP");
  (polyfunc).Draw("same");
  polyfunc.SetTitle("Interpolating function"); // Por deficiência do ROOT, há limitação em colocar nomes de eixos em TF1s (de acordo com ROOTforum)
  canvas->Modified();
  
  (graphpoints).Write();
  (polyfunc).Write();
  canvas->Write();

  
  //alínea b)

  cout << endl << endl << "Alínea b):" << endl << endl;

  double erros[ALINEA_B_NPONTOS];
  double array_n[ALINEA_B_NPONTOS];

  for (int i = 0; i < ALINEA_B_NPONTOS; i++) {

    array_n[i] = 4.*(1.+i);
    //cout << "n: " << fixed << setprecision(6) << array_n[i] << endl;
    Vandermonde v (array_n[i], x, y, test_TF1); // *test_TF1
    //cout << i << ": " << v.GetMatrix() << endl;
    erros[i] = TMath::Log10(v.GetCoeffError());
    cout << "Log base 10: " << erros[i] << endl;
  }
  

  TGraph* gErrors = new TGraph(ALINEA_B_NPONTOS, array_n, erros);
  gErrors->SetName("gErrors");
  gErrors->SetMarkerStyle(21);
  gErrors->SetMarkerColor(39);
  gErrors->SetMarkerSize(2);
  gErrors->SetLineColor(kGreen+2);
  gErrors->SetLineStyle(1);
  gErrors->SetLineWidth(2);
  gErrors->SetTitle("log_{10}(#DeltaE) in function of n");
  gErrors->GetXaxis()->SetTitle("n");
  gErrors->GetYaxis()->SetTitle("log_{10}(#DeltaE)");

  gErrors->Write();

  //alínea c)

  cout << endl << endl << "Alínea c):" << endl << endl;

  FCmatrixFull C = vand.GetMatrix();
  cout << "Matriz de Coeficientes: " << C << endl;
  FCmatrixFull D(C);
  
  vand.GetInverseMatrix (C);
  cout << "Inversa da Matriz de Coeficientes: " <<  C << endl;  

  /*cout << "Inversa*Original: " << C*D << endl;
  cout << "Original*Inversa: " << D*C << endl;

  cout << "Vetor b:" << vand.GetCoefficients() << endl;*/


  //fim
  file->Close();
  delete gErrors;
  
  return 0;
}
