#include <stdio.h>
int main ()
{
  float x, mu;
  int i;
  i=0;
  printf ("Lei de Malthus\n");
  printf ("Digite o valor inicial de x (valor entre 0, inclusive, e 1, inclusive):\n");
  scanf ("%f", &x);
  printf ("Digite o valor da razão da progressão geométrica (valor entre 0, inclusive, e 1, inclusive):\n");
  scanf ("%f", &mu);
  if ((x>=0) && (x<=1) && (mu>=0) && (mu<=1))
    {
      printf ("Eis os primeiros 20 valores da sucessão:\n");
      while (i<=20)
	{
	  x = x*mu;
	  printf ("%f"\n, x);
	  i+=1;
	}
    }
  else
    printf ("Digitou valor(es) inválido(s).\n");
  return 0;
}
  
