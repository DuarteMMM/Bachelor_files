#include "NevilleInterpolator.h"
#include "LagrangeInterpolator.h"
#include "NewtonInterpolator.h"
#include "Spline3Interpolator.h"

#include "TF1.h"
#include "TH1.h" // Axis names
#include "TCanvas.h"
#include "TApplication.h"

#include <iostream>


using namespace std;


int main() {

  //double z[3] = {-1.2, 0.3, 1.1};
  //double y[3] = {-5.76, -5.61, -3.69};
  double x[6] = {0., 0.5, 1., 1.5, 2., 2.5};
  double y[6] = {0., sin(0.5), sin(1.), sin(1.5), sin(2.), sin(2.5)};
  //double x[20] = {-1., -0.5, 0.4, 1.3, 1.4, 1.5, 1.8, 2.1, 2.3, 3.4, 5.6, 6.1, 7.5, 7.8, 8.1, 8.6, 8.9, 9.0, 10., 10.6};
  //double y[20] = {-4., -3. , 0. , 1. , 3. , 2. , 5. , 7. , 3. , 2. , 1. , 0. , -1., -5., -6., -5., -1., 0. , 1. , 5.  };
  
  //NevilleInterpolator neville(3, z, y, nullptr);
  //NewtonInterpolator newton(6, x, y, nullptr);
  //LagrangeInterpolator lagrange(6, x, y, nullptr);
  Spline3Interpolator spline(6, x, y);

  //double x_value = 1.2;
  //double y_value = newton.Interpolate (x_value);
  //cout << "Valor em x=" << x_value << ": " << y_value << endl;
  

  TApplication tapp ("app", 0, 0);
  TCanvas* canvas = new TCanvas("cc", "", 0, 0, 1000, 800);
  
  //TCanvas* canvas = newton.GetCanvas(); // Outra forma
  
  //neville.DataPoints::Draw();
  //neville.Draw();
  
  //newton.DataPoints::Draw();
  //newton.Draw();

  //lagrange.DataPoints::Draw();
  //lagrange.Draw();

  //spline.DataPoints::Draw();
  spline.Draw();

  canvas->Modified();
  tapp.Run();
}
