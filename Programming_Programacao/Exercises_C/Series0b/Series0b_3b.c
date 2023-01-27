#include <stdio.h>
int main ()
{
  float x, mu;
  int i, a;
  i=0;
  printf ("Lei de Malthus\n");
  printf ("Digite o valor inicial de x (valor entre 0, inclusive, e 1, inclusive):\n");
  scanf ("%f", &x);
  printf ("Digite o valor da razão da progressão geométrica (valor entre 0, inclusive, e 1, inclusive):\n");
  scanf ("%f", &mu);
  if ((x>=0) && (x<=1) && (mu>=0) && (mu<=1))
    {
      printf ("Quantos valores da sucessão deseja saber?\n");
      scanf ("%d", &a);
      printf ("Eis os outros %d valores da sucessão: \n", a);
      while (i<a)
	{
	  x = x*mu;
	  printf ("%f\n", x);
	  i+=1;
	}
    }
  else
    printf ("Digitou valor (es) inválido(s).\n");
  return 0;
}
