#include <iostream>
#include <limits>

int main()
{
  std::cout << "\n-----Exercício 43-----\n";
  // Alínea a
  int resultado = 2147483600;
  // Já sei a priori que o máximo é 2147483647, logo começei perto...
  std::cout << "\nAlguns valores sucessivos:\n";
  while (resultado >= 0)
    {
      resultado = resultado + 1; // Fiz para 1 e não 2, como dizia no enunciado
      std::cout << resultado << std::endl;
    }
  std::cout << "Conclui-se que o limite superior é " << resultado-1 << ".\n" << std::endl;
  resultado = -2147483600;
  while (resultado < 0)
    {
      resultado = resultado - 1; // Fiz para 1 e não 2, como dizia no enunciado
      std::cout << resultado << std::endl;
    }
  std::cout << "Conclui-se que o limite inferior é " << resultado+1 << "." << std::endl;

  // Alíneas b e c (com batota...)
  std::cout << "\nO máximo float é " <<  std::numeric_limits<float>::max() << " e o mínimo float é " << std::numeric_limits<float>::min() << ".\n" << std::endl;
  std::cout << "O máximo double é " <<  std::numeric_limits<double>::max() << " e o mínimo double é " << std::numeric_limits<double>::min() << ".\n" << std::endl;

  std::cout << "\n-FIM-\n\n";
 
  return 0;
}
