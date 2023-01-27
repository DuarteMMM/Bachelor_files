#include "Vec.h"

#include <iostream>

using namespace std;


int main() {

  double d[3] = {0, 1, 2};

  Vec v(3,d);

  cout << v << endl;

  v.AddEntry(6);

  cout << v << endl;
}
