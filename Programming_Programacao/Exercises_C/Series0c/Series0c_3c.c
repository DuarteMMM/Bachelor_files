#include <stdio.h>
int main()
{
 int i, i1, soma;
 soma=0;
 float x, r, x_ref;
 i=0;
 i1=0;
 printf("Digite o valor inicial, entre 0 e 1: \n");
 scanf("%f",&x);
 printf("Digite o valor de r, entre 0 e 4: \n");
 scanf("%f",&r);
 if ((r>=0) && (r<=4) && (x>=0) && (x<=1))
 {
  while (i<=999)
  {
   x=x*r*(1-x);
   i=i+1;
  }
  x_ref=x;
  printf("Valor(es) de estabilização:\n");
  while (i1<=63)
  {
   x=x*r*(1-x);
   printf("%f\n", x);
   i1=i1+1;
   soma=soma+1;
   if (x==x_ref)
   {
    break;
   }
  }
  printf("Há %d valor(es).\n NOTA: se forem mais de 64 valores, os restantes não foram considerados...\n", soma);
 }
 else
 {
  printf ("Valor(es) inválido(s).\n");
 }
 return 0;
}
