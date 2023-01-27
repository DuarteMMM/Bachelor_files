#include <cmath>
#include <iostream>

using namespace std;

int main() {

  double fE = [] (int n, int Z) -> double

  {

    double En = -2.1798723e-18 * pow(Z,2) / pow(n,2);

    return En;

  } (1,2);

  cout << "Em J:" << fE << endl << "Em eV:" << fE*6.24150913e18 << endl;
  
  return 0;

}
