/******************************************************
 *                Física Computacional                *
 *                    Exercício 27                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream>
#include "Exercicio27_Box.h"
using namespace std;

int main() {
  // Criar dois cubos de lado 1
  Box B1;
  Box B2 = B1;

  // Somar dois cubos
  Box B3 = B1 + B2;

  // Criar dois paralelepípedos
  Box B5(1, 1, 2);
  Box B6(B5);

  // Somar os dois paralelepípedos
  Box B7;
  B7 = B5 + B6;

  // Calcular volumes
  float volume_3 = B3.getVolume();
  float volume_7 = B7.getVolume();

  cout << "\n--- Exercício 27 ---\n\nVolume de 3: " << volume_3 << "\nVolume de 7: " << volume_7 << endl;
  
  // Somar volumes com ponteiros, em vez da maneira anterior
  Box* pB1 = new Box ();
  Box* pB2 = new Box ();
  Box* pB3 = pB1->Add(pB2);
  cout << "\nVolume de 3 usando outro método: " << pB3->getVolume() << "\n\n-FIM-" << endl;

  return 0;
}
