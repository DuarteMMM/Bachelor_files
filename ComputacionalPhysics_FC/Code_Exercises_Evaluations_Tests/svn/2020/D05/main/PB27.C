#include <iostream>
#include "../src/PB27_box.h"

using namespace std;

int main () {
  
  // criar dois cubos de lado 1
  Box B1;
  Box B2 = B1;
  
  // somar dois cubos
  Box B3 = B1 + B2;
  
  // criar dois paralelipipedos
  Box B5(1,1,2);
  Box B6(B5);
  
  // somar os dois paralelipipedos
  Box B7;
  B7 = B5 + B6;
  
  // calcular volumes
  float volume_3 = B3.getVolume();
  float volume_7 = B7.getVolume();
  cout << "volumes: " << volume_3 << " " << volume_7 << endl;

  Box* pB1 = new Box(1,2,3);
  Box* pB2 = new Box(4,5,6);
  Box* pB3 = pB2->Add(pB1);
  cout << "Volume de pB3: " << pB3->getVolume() << endl;

  
  return 0;

}
