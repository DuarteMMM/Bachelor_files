// Para esclarecer com um exemplo, ver o link https://binary-system.base-conversion.ro/real-number-converted-from-decimal-system-to-32bit-single-precision-IEEE754-binary-floating-point.php?decimal_number_base_ten=-1.625&sign=1&exponent=01111111&mantissa=10100000000000000000000

#include <iostream>

int main()
{
  std::cout << "\n-----Exercício 42-----\n\nAlínea a: o expoente verdadeiro é 14-127 = -113 (base 10);\nAlínea b: 1.625 convertido para binário fica 1.1010000..., mas tira-se o primeiro 1, porque todos os números em binário têm esse 'hidden 1';\nAlínea c: o número real é, portanto, +1.625x10^(-113).\n\n-FIM-\n\n";
  
  return 0;
}
