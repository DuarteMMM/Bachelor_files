#include <stdio.h>
int main ()
{
  float f, c, teste;
  printf ("Insira os graus, em Celsius: \n");
  teste = scanf ("%f", &c);
  if (teste!=1)
    {
      printf ("o valor que inseriu não é válido.\n");
      return 1;
    }
  f = c*1.8+32;
  printf ("%.1f graus Celsius equivalem a %.1f graus Fahrenheit.\n", c, f);
  return 0;
}
