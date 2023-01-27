#include <cmath>
#include <iostream>

using namespace std;

double sum(int* vi, int* vj) {

  double sum = 0;
  
  for (int i = 0; i <= *vi; i++) {

    for (int j = 5; j <= *vj; j++) {

      sum += cos(i*i + sqrt(j));

    }

  }

  return sum;

}
