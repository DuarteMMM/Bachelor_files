#include <iostream>
using namespace std;

int main()
{
  cout << "\n-----Exercício 44-----\n";
  float numero = 1.1;
  float incremento = 0.1;
  while (numero != 1.)
    {
      incremento *= 0.1;
      numero = 1.;
      numero += incremento;
    }
  cout << "\nConcluiu-se que a precisão em float é " << incremento/0.1 << ".\n";

  double numero1 = 1.1;
  double incremento1 = 0.1;
  while (numero1 != 1.)
    {
      incremento1 *= 0.1;
      numero1 = 1.;
      numero1 += incremento1;
    }
  cout << "\nConcluiu-se que a precisão em double é " << incremento1/0.1 << ".\n\n-FIM-\n\n";

  return 0;
}
