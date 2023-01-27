#include "DataManip.h"
#include <utility> // pair
#include <iostream> //cout
#include <vector> // Inúmeras coisas...
#include <algorithm> // sort
#include <numeric> // adjacent_difference
#include <cstdio> // printf
#include <string> // string no construtor, [%s] nos prints
#include "TH1D.h"
#include <math.h>


using namespace std;


typedef vector<pair<double, double>> VecPair;


DataManip::DataManip (const string s) : DataReader(s) {


  //create DerivativeVector
  vector<double>  ssn_in, t_in;
  vector<double> ssn_out(DataVector.size()), t_out(DataVector.size());
  
  for(auto DV_iterator : DataVector) {

    ssn_in.push_back(DV_iterator.second);
    t_in.push_back(DV_iterator.first);

  }


  
  adjacent_difference(ssn_in.begin(),
		      ssn_in.end(),
		      ssn_out.begin());


  
  adjacent_difference(t_in.begin(),
		      t_in.end(),
		      t_out.begin());


  
  auto DV_Iterator = DataVector.begin();
  auto ssn_out_iterator = ssn_out.begin();
  
  for(auto t_out_iterator = t_out.begin(); t_out_iterator != t_out.end(); t_out_iterator++) {

    pair<double,double> p;
    p.first = DV_Iterator->first;
    p.second = *ssn_out_iterator/(*t_out_iterator);

    DerivativeVector.push_back(p);

    DV_Iterator++;
    ssn_out_iterator++;
  }


  //create DerivativeGraph
  
  DerivativeGraph = new TGraph(DerivativeVector.size());

  int i = 0;
  
  for(pair<double, double> v: DerivativeVector) {

    DerivativeGraph->SetPoint(i, v.first, v.second);
    i++;
    
  }

  DerivativeGraph->SetName("GdataDeriv");
  DerivativeGraph->SetMarkerColor(kGreen+2);
  DerivativeGraph->SetMarkerStyle(20);
  DerivativeGraph->SetMarkerSize(0.4);
  
}


VecPair DataManip::GetDataVectorSorted (int n) {
  printf ("[%s] called...\n", __PRETTY_FUNCTION__);
  VecPair vec;
  vec = DataVector; // Igualar ao vetor "original"

  // ordem descendente (do segundo elemento)
  if (n == 0)
    sort (vec.begin(), vec.end(), [](const pair<double,double> &a, const pair<double,double> &b) { return (a.second > b.second);}); // Mesmo link que em baixo

  // ordem ascendente (do segundo elemento)
  if (n == 1)
    sort (vec.begin(), vec.end(), [](const pair<double,double> &a, const pair<double,double> &b) { return (a.second < b.second);}); // Em "https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/"

  return vec;
}


VecPair DataManip::GetDataDerivativeVector() {
  printf ("[%s] called...\n", __PRETTY_FUNCTION__);

  return DerivativeVector;
}			  


TGraph* DataManip::GetDataDerivativeGraph() {
  
  return DerivativeGraph;

}

TH1D* DataManip::GetDataDerivativeHisto() {

  TH1D* hist = new TH1D("HdataDeriv", "Sunspot Data", 200, -5000, 5000);
  
  for(pair<double, double> v: DerivativeVector) {

    hist->Fill(v.second);
    
  }

  //hist->SetName("HdataDeriv");
  
  return hist;

}

vector<pair<double, double> > DataManip::GetMovingAverage(int M) {
  VecPair MediaDeslizante;
  
  vector<double> s_copia(DataVector.size());
  vector<double> s_media(DataVector.size());

  int contador=0;
  int max = DataVector.size();
  
  while (contador < max)
    {
      s_copia[contador] =  (DataVector[contador].second);
      contador++;
    }
  contador = 0;
  
  int lim_inf = M/2 - 1;
  int qt_inf = lim_inf + 1;
  int qt_intermedios = DataVector.size() - M + 1;
  int lim_sup = DataVector.size() - M/2;
  double soma=0.;
  double media;

  copy_n (s_copia.begin(), qt_inf, s_media.begin()); // Atribuir a s_media valores até ordem M/2-1
  for_each (s_copia.begin(), s_copia.begin()+(M-1), [&soma] (int n) {soma += n;}); // Calcular o primeiro somatório
  media = soma/M;
  s_media.push_back (media);
  contador += qt_inf+1; // Valores já adicionados a s_media
  
  int contador1 = 0;
  int contador2 = M-1;
  
  while (contador1 < qt_intermedios)
    {
      soma = soma-s_copia[contador1]+s_copia[contador2+1]; // Alterar o somatório
      media = soma/M; // Nova média
      s_media[contador] = media; // Colocar a média no vetor
      contador++;
      contador1++;
      contador2++;
    }

  // Adicionar os elementos finais
  copy (s_copia.begin() + lim_sup, s_copia.end(), s_media.begin()+lim_sup);

  
  auto iterator_DV = DataVector.begin();
  auto s_media_iterator = s_media.begin();
  int max1 = DataVector.size();
  
  for (int g=0; g<max1; g++){
    pair<double,double> par;
    par.first = iterator_DV->first;
    par.second = *s_media_iterator;
    
    MediaDeslizante.push_back(par);
    
    iterator_DV++;
    s_media_iterator++;
  }

  s_media.clear();
  s_copia.clear();
  
  return MediaDeslizante;
}

TGraph* DataManip::GetMovingAverageGraph (int num, const char* s){
  VecPair MediaData = GetMovingAverage (num);
  
  TGraph* MediaGraph = new TGraph (MediaData.size());
  int contador = 0;
  
  for (pair<double, double> par : MediaData) {
    MediaGraph->SetPoint (contador, par.first, par.second);
    contador++;
  }
  
  MediaGraph->SetName(s);
  if (num == 11)
    MediaGraph->SetMarkerColor(kYellow);
  if (num == 181)
    MediaGraph->SetMarkerColor(kMagenta);
  
  MediaGraph->SetMarkerStyle(20);
  MediaGraph->SetMarkerSize(0.4);

  return MediaGraph;
}

TGraph* DataManip::GetAutocorrelationGraph(double kmin, double kmax, double time_step, string nome){

  TGraph* correlation_graph = new TGraph();
  correlation_graph->SetName(nome.c_str());

  int n = 0;

  cout << "Início do for de calculate coeficients" << endl;
  for (double i = kmin; i <= kmax; i += time_step) {

    ++n;
    correlation_graph->SetPoint(n, i, CalculateCorrelationCoeficient(i));
    cout << "Cálculo bem sucedido:" << n << endl;
  }
  cout << "Fim do for de calculate" << endl;
  correlation_graph->SetMarkerStyle(22);
  correlation_graph->SetMarkerSize(0.4);

  if (nome == "Gcorr") {
    
    correlation_graph->SetMarkerColor(kGreen+2);

  } else {

    correlation_graph->SetMarkerColor(kGreen+4);

  }
    
  return correlation_graph;
}
  

double DataManip::CalculateCorrelationCoeficient(double k) {

  double r;
  double average1, average2;
  double expectation = 0, stddev1 = 0, stddev2 = 0;
  

  average1 = CalculateAverage(1849., 2020.-k);
  average2 = CalculateAverage(1849.+k, 2020.);

  for(auto a = DataVector.begin(); a->first <= (2020.-k); a++) {
    
    auto ak = FindCorrespondingElement(a,k);
    auto dev1 = (a->second - average1);
    auto dev2 = (ak->second - average2);
    
    expectation += dev1*dev2;
    stddev1 += dev1*dev1;
    stddev2 += dev2*dev2;
    
  }

  r = expectation / (sqrt(stddev1) * sqrt(stddev2));
  
  return r;
}


double DataManip::CalculateAverage(double i, double f) {

  vector<pair<double, double> >::iterator beginning_of_interval;
  double average = 0, size = 0;
  
  //find iterator to the beginning of the interval
  for(auto a = DataVector.begin(); a != DataVector.end(); a++) {

    if(a->first == i) {

      beginning_of_interval = a;
      size = 1.;
      
    } else if ((a->first > i) && (a->first < f)) {

      size++;
      
    } else if(a->first == f) {
      
      size++;
      break;
      
    }
  }
  
  
  //calculate the average
  for(auto a = beginning_of_interval; a->first <= f; a++) {

    average += a->second/size;

  }

  return average;
}


vector<pair<double, double> >::iterator DataManip::FindCorrespondingElement(vector<pair<double, double> >::iterator original, double deviation) {
  
  vector<pair<double, double> >::iterator result;
  auto a = original;

  int sign_k = deviation/abs(deviation);
  
  for(a; abs((original->first + deviation - a->first)) > 0.03; a+=sign_k) {

    result = a;
    cout << result->first << endl;
  }

  a++;
  result = a;
  
  return result;
}
