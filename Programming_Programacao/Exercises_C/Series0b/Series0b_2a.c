# include <stdio.h>
int main ()
{
  float c, f;
  printf ("Introduza a temperatura e, graus Celsius:\n");
  scanf ("%f", &c);
  f = c*1.8+32;
  printf ("%.4f graus Celsius equivalem a %.4f graus Fahrenheit.\n", c, f);
  return 0;
}

  
