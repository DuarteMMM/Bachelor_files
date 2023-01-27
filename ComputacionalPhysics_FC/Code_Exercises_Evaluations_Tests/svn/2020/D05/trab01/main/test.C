#include "DataReader.h"
#include "DataManip.h"
#include <vector>
#include <iostream>


using namespace std;


int main() {

  DataManip D("SunspotNumberDATA2020.txt");

  if (DataReader::FileExists("SunspotNumberDATA2020.txt")) {

    //cout << "It exists!" << endl;

  } else {

    //cout << "It does not exist!" << endl;
    exit(1);

  }
 
  for(pair<double, double> p: D.GetDataVector()) {

    //cout << p.first << " - " << p.second << endl;

  }

  //cout << (D.GetDataVector())[0].second << endl;


  auto v = D.GetDataVectorSorted(0);

  for (int i = 0; i<10; i++) {

    //cout << setprecision(7) << v[i].first << " - " << v[i].second << endl;

  }

  //cout << v.size() << endl;

  D.GetDataDerivativeVector();

  /*for(pair<double, double> p: D.GetDataDerivativeVector()) {

    //cout << p.first << " - " << p.second << endl;

    }*/

  auto Vsmooth181 = D.GetMovingAverage(181);
  int jj=0;
  cout << "\n\n-------------\n\n";
  /* while (jj < Vsmooth181.size())
    {
      //cout << Vsmooth181[jj].first << " - " << Vsmooth181[jj].second << endl;
      jj++;
      }*/

  D.GetAutocorrelationGraph(0., 2., 0.50, "Gcorr");

  return 0;
}


