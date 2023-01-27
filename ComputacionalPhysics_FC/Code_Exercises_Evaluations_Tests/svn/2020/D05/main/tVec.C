#include "Vec.h"
#include <iostream>


using namespace std;


int main () {

  Vec a;
  
  Vec b(3, 4.);

  double x[5] = {1,2,3,4,5};

  Vec c(3, x);

  Vec d(c);

  cout << a << endl;
  cout << b << "," << b[1] << endl;
  cout << c << endl;
  cout << d << endl;

  a = c;

  cout << a.dot(b) << endl;
  a.swap(0,1);
  cout << a << endl;
  cout << a.size() << endl;
  cout << a.sumAbs() << endl;
  
  return 0;
}
