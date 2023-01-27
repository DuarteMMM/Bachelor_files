#ifndef __DataManip__
#define __DataManip__

#include "DataReader.h"
#include <utility> // std::pair, std::make_pair
#include <string> // Constructor"
#include "TH1D.h"
#include "TGraph.h"


using namespace std;


typedef vector<pair<double, double>> VecPair;


class DataManip : public DataReader {
  
private:
  VecPair DerivativeVector;
  TGraph* DerivativeGraph;

  double CalculateCorrelationCoeficient(double);
  double CalculateAverage(double, double);
  vector<pair<double, double> >::iterator FindCorrespondingElement(vector<pair<double, double> >::iterator, double);


public:

  
  DataManip (const string); // constructor (não sei que ficheiro dar como default...)

  ~DataManip () = default; // default destructor

  VecPair GetDataVectorSorted (int n); // Obter o vetor ordenado de acordo com o segundo elemento (alínea c)
  
  VecPair GetDataDerivativeVector(); // Obter vetor das derivadas temporais do sunspot em função da data

  TGraph* GetDataDerivativeGraph();

  TH1D* GetDataDerivativeHisto();

  vector<pair<double, double> > GetMovingAverage(int);

  TGraph* GetMovingAverageGraph(int, const char*);

  TGraph* GetAutocorrelationGraph(double, double, double, string);
};

#endif
