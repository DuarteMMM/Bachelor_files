/******************************************************
 *                Física Computacional                *
 *                    Exercício 5                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream> // std::cout
#include <limits>   // std::numeric_limits

int main () {

  std::cout << "\n-=-=-=- Limites de tipos de variáveis -=-=-=-=-\n\n" << std::endl;
  
  std::cout << "Valor mínimo para int: " << std::numeric_limits<int>::min() << std::endl;
  std::cout << "Valor máximo para int: " << std::numeric_limits<int>::max() << '\n' << std::endl;
  
  std::cout << "Valor mínimo para unsigned int: " << std::numeric_limits<unsigned int>::min() << std::endl;
  std::cout << "Valor máximo para unsigned int: " << std::numeric_limits<unsigned int>::max() << "\n" << std::endl;
  
  std::cout << "Valor mínimo para float: " << std::numeric_limits<float>::min() << std::endl;
  std::cout << "Valor máximo para float: " << std::numeric_limits<float>::max() << "\n" << std::endl;
  
  std::cout << "Valor mínimo para double: " << std::numeric_limits<double>::min() << std::endl;
  std::cout << "Valor máximo para double: " << std::numeric_limits<double>::max() << "\n" << std::endl;
  
  return 0;
}
