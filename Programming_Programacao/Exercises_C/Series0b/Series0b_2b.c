# include <stdio.h>
int main ()
{
  float c, f;
  printf ("Deseja converter graus Celsius em Fahrenheit ou Fahrenheit em Celsiu?\n");
  printf ("[1] - Graus Celsius em Fahrenheit\n");
  printf ("[2] - Graus Fahrenheit em Celsius\n");
  int a;
  scanf ("&d", &a);
  if (a==1);
  {
    printf ("Introduza a temperatura em graus Celsius:\n");
    scanf ("%f", &c);
    f = c*1.8+32;
    printf ("%.4f graus Celsius equivalem a %.4f graus Fahrenheit.\n", c, f);
  }
  if (a==2)
    {
      printf ("Introduza a temperatura em graus Fahrenheit:\n");
      scanf ("%f", &f);
      c = (f-32)/1.8;
      printf ("%.4f graus Fahrenheit equivalem a %.4f graus Celsius.\n", f, c);
    }
  if ((a!=1) && (a!=2))
    printf ("Introduziu uma opção inválida.\n");
  return 0;
}
