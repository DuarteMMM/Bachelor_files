#include <stdio.h>
int main()
{
  float c,f;
  c = 0.0;
  printf "Graus Celsius     Graus Fahrenheit\n");
  while (c<=100.1)
    {
      f=c*1.8+32;
      printf ("%6.1f     %8.1f\n"c, f);
      c += 1;
    }
  return 0;
}

    
