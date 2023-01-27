#ifndef __DataReader__

#define __DataReader__

#include <string>
#include <vector>
#include <utility>
#include "TGraph.h"

using namespace std;

class DataReader {

protected:

  vector<pair<double, double> > DataVector; //4 - time in fraction of year; 5 - sunspot number
  TGraph* DataGraph;
  int lastofDV;

private:

  void DataParser(string*);

public:

  DataReader(string);

  ~DataReader();

  static bool FileExists(string);

  vector<pair<double, double> > GetDataVector();

  TGraph* GetDataGraph();

};


#endif
