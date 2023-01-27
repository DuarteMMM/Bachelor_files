#include <cmath>
#include <iostream>

using namespace std;

int main() {

  double E[10][20];

  for(int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {

      E[i][j] = [] (int n, int Z) -> double  {return -2.1798723e-18 * pow(Z,2) / pow(n,2);} (i+1,j+1);

      cout << "n = " << j + 1 << ", z = " << i + 1 << ", E = " << E[i][j] << endl;
    }
  }
  
  return 0;

}
