#include <stdio.h>
int main()
{
 int i, i1;
 float r, x, x_ref, x1;
 i=0;
 i1=0;
 printf ("Digite o valor inicial, entre 0 e 1: \n");
 scanf ("%f", &x);
 x1=x;
 printf ("Digite o valor de r, entre 0 e 3.82: \n");
 scanf ("%f", &r);
 if ((r>=0) && (r<=3.83) && (x<=1) && (x>=0))
 {
  while (i<=1000)
  {
   x=r*x*(1-x);
   i=i+1;
   x_ref=x;
  }
  while (i1<=1000)
  {
   x1=r*x1*(1-x1);
   printf("%f\n", x1);
   i1=i1+1;
   if (x1==x_ref)
   {
    break;
   }
  }
  printf("Chegou ao valor de estabilização.\n");
 }
 else
 {
  printf ("Digitou 1 ou 2 valor(es) inválido(s).\n");
 }
 return 0;
}
