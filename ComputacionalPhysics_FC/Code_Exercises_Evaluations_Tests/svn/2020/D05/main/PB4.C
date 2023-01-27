#include <cmath>
#include <cstdio>

using namespace std;

int main () {

  float pi_f = 0;
  double pi_d = 0;

  pi_d = 4*atan(1);
  pi_f = (float) pi_d;

  printf("Pi em float: %.12f\nPi em double: %.20f\n", pi_f, pi_d);

  return 0;

}
  
