#include "DataPoints.h"

#include <algorithm>
#include <stdexcept>
#include <iostream> //ostream
#include <iomanip> //setprecision
#include <cstdlib> //abs

#include "TGraph.h"
#include "TAxis.h"

using namespace std;


DataPoints::DataPoints() : N(0), x(nullptr), y(nullptr), gPoints(nullptr) {;}


DataPoints::DataPoints(unsigned int N_ext, const double* x_ext, const double* y_ext) : N(N_ext), x(new double[N]), y(new double[N]), gPoints(nullptr) {

  if (!x_ext || !y_ext)
    throw invalid_argument(Form("[%s]: null or invalid arrays!", __PRETTY_FUNCTION__)); 

  //copy arrays
  copy(x_ext, x_ext + N, x);
  copy(y_ext, y_ext + N, y);
  
  //retrieve min and max
  UpdateMinMaxX();
  UpdateMinMaxY();
  
  //create Graph
  gPoints = new TGraph(N, x, y);
  gPoints->SetMarkerStyle(20);
  gPoints->SetMarkerColor(4);
  gPoints->SetMarkerSize(1.5);
  gPoints->SetTitle("Interpolating function");

  gPoints->GetXaxis()->SetTitle("x");
  gPoints->GetYaxis()->SetTitle("y");
  gPoints->GetXaxis()->SetLimits(xmin -0.1 * ( (abs(xmin)+abs(xmax)) /2. ), xmax + 0.1*( (abs(xmin)+abs(xmax)) /2. ) );
  gPoints->GetYaxis()->SetRangeUser (ymin - 0.1*( (abs(ymin)+abs(ymax)) /2. ), ymax + 0.1*( (abs(ymin)+abs(ymax)) /2. ) );
  
}


DataPoints::~DataPoints() {

  if (x) delete[] x;
  if (y) delete[] y;

  if (gPoints) delete gPoints;
  
}


/////////////////////////////////////////////////////graphics


const TGraph& DataPoints::GetGraph() const{

  return *gPoints;

}


void DataPoints::Draw() const{

  gPoints->Draw("AP");

}


////////////////////////////////////////////////setters


void DataPoints::UpdateMinMaxX() {

  auto it = minmax_element(x, x+N);
  xmin = *it.first;
  xmax = *it.second;

}


void DataPoints::UpdateMinMaxY() {

  auto it = minmax_element(y, y+N);
  ymin = *it.first;
  ymax = *it.second;

}


///////////////////////////////////////friends


ostream& operator<< (ostream& s, const DataPoints& data) {

  s << "Number of Points stored:" << data.N << endl;
  
  for (int i = 0; i < data.N; ++i) {

    s << fixed << setprecision(3) << "(" << data.x[i] << "," << data.y[i] << ")" << endl;

  }

  return s;
}
