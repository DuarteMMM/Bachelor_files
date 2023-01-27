#ifndef __DATAPOINTS__
#define __DATAPOINTS__

#include <iostream>
#include <string>

#include "TGraph.h"


using namespace std;


class DataPoints {

  
 public:
  //constructors + destructor
  DataPoints();
  DataPoints(unsigned int, const double*, const double*);
  virtual ~DataPoints();

  //interpolation
  virtual double Interpolate (double x) {return 0;}

  //graphics
  const TGraph& GetGraph() const;
  virtual void Draw() const; 

  //output
  friend ostream& operator<<(ostream&, const DataPoints&);

 protected:
  
  int N;
  double *x, *y;

  TGraph* gPoints;

  double xmin, xmax, ymin, ymax;

  void UpdateMinMaxX();
  void UpdateMinMaxY();

};


#endif
