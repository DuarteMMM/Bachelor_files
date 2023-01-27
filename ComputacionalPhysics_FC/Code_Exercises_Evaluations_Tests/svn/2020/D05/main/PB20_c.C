#include <cmath>
#include <iostream>

using namespace std;

int main() {

  double me = 2, ce = 3, h = 5, e0 = 7, c = 3;
  
  double fE = [me, ce, e0, h, c] (int ni, int nf, int Z) -> double

  {

    double lambda = h * c / ( pow(Z,2)*me*pow(ce,4)/(8*pow(h,2)*pow(e0,2)) * ( pow(ni,2) - pow(nf,2)/ pow(nf,2)*pow(ni,2)) );

    return lambda;

  } (1, 2, 5);

  cout << "Em J:" << fE << endl << "Em eV:" << fE*6.24150913e18 << endl;
  
  return 0;

}
