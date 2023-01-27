#include "DataReader.h"
#include <fstream> //ifstream
#include <cstring> //strtok
#include <iostream> //cout
#include <string> //string
#include <sstream> //stringstream
#include "TGraph.h"//TGraph
#include <vector>//vector
#include <utility> //pair

#define NUMBER_OF_MEANINGLESS_DATA_LINES 11323

#define NUMBER_OF_COLUMNS 7


using namespace std;


DataReader::DataReader(string filename) {

  ifstream datafile (filename);
  string receiver[8], fileline;
  lastofDV = 0;
  
  //check if file opened
  if(!datafile) {

    cout << "Erro a abrir o ficheiro.\n";
    exit(1);

  }

  datafile.seekg(0, datafile.end);
  int file_size = datafile.tellg();
  datafile.seekg(0, datafile.beg);

  
  //skip lines due to meaningless data
  string string_dump;
  
  for (int i = 0; i < NUMBER_OF_MEANINGLESS_DATA_LINES; ++i) {

    getline(datafile, string_dump);

  }

  
  //read data
  while(datafile.tellg() < file_size) {

    
    getline(datafile, fileline);
    char* fileline_cstring = strdup(fileline.data());
    receiver[0] = strtok(fileline_cstring, " ");
#ifdef DEBUG
    cout << receiver[0] << endl;
#endif
    
    
    //split line into strings (by column)
    for (int i = 1; i < NUMBER_OF_COLUMNS; i++) {

      receiver[i] = strtok(NULL, " ");

#ifdef DEBUG
      cout << receiver[i] << endl;
#endif
      
    }

#ifdef DEBUG
    cout << "Calling Data Parser" << endl;
#endif
    //use DataParser to save the data
    DataParser(receiver);
    lastofDV++;
#ifdef DEBUG
    cout << "Successfully called Dataparser" << endl;
    cout << datafile.tellg() << " of " << file_size << endl;

#endif

    
  }
   
  datafile.close();


  //build DataGraph

  DataGraph = new TGraph(DataVector.size());

  int i = 0;
  for(pair<double, double> v: DataVector) {

    DataGraph->SetPoint(i, v.first, v.second);
    i++;
    
  }

  DataGraph->SetName("Gdata");
  DataGraph->SetMarkerColor(kBlue+1);
  DataGraph->SetMarkerStyle(20);
  DataGraph->SetMarkerSize(0.4);
  
}


DataReader::~DataReader() {

  DataVector.clear();
  
  delete DataGraph;
  
}


void DataReader::DataParser(string* data_strings) {

  pair<double, double> temp_pair;
  double a = 0, b = 0;

  
  stringstream ss3 (data_strings[3]);
  stringstream ss4 (data_strings[4]);

  //data_strings[3] e [4] correspond to columns 3 and 4 of the file, the only ones that matter to us

  ss3 >> temp_pair.first;
  ss4 >> temp_pair.second;

  DataVector.push_back(temp_pair);
}


bool DataReader::FileExists(string filename) {

  ifstream filestream (filename);

  if(filestream) {

    return true;

  } else {

    return false;

  }

}


vector<pair<double, double> > DataReader::GetDataVector() {

  return DataVector;

}


TGraph* DataReader::GetDataGraph() {

  return DataGraph;

}
