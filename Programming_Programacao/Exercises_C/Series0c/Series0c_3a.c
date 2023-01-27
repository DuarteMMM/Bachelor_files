#include <stdio.h>
int main()
{
 int i;
 float r, x;
 i=0;
 printf ("Digite o valor inicial, entre 0 e 1: \n");
 scanf ("%f", &x);
 printf ("Digite o valor de r, entre 0 e 4: \n");
 scanf ("%f", &r);
 if ((r>=0) && (r<=4) && (x<=1) && (x>=0))
 {
  printf ("Primeiros 1000 valores: \n");
  printf ("%f\n", x);
  while (i<=999)
  {
   x=r*x*(1-x);
   printf("%f\n", x);
   i=i+1;
  }
 }
 else
 {
  printf ("Digitou um ou dois valore(s) incorreto(s).\n");
 }
 return 0;
}
