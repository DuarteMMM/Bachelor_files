#include <stdio.h>
int main()
{
  int a, b, c, teste;
  b=0;
  printf ("Insira o número natural menor que 50 cuja tabuada deseja saber:\n");
  teste=scanf ("&d", &a);
  if (teste!=1 || (a<0) || (a>=50))
    {
      printf ("Inseriu algo inválido.\n");
      return 1;
    }
  while (b<=10)
    {
      c=a*b;
      printf ("%d x %d = %d\n", a, b, c);
      b+=1;
    }
  return 0;
}
