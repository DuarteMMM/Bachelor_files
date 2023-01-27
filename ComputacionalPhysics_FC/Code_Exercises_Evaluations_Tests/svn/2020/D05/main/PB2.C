#include <cstdio>
#include <cmath>


double calculateF (double x) {

  return sin(x)*sin(x);

}


double calculateZ (double x) {

  return x + calculateF(x);

}


int main() {

  printf("z(0.4) = %f\nz(2.1) = %f\nz(1.5) = %f\n", calculateZ(0.4), calculateZ(2.1), calculateZ(1.5));

  return 0;

}
