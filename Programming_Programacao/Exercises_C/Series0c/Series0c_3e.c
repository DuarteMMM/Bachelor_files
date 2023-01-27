#include <stdio.h>
int main()
{
 int i, i1, i2, soma;
 FILE *f1;
 f1 = fopen ("órbitas Malthus", "wt");
 soma=0;
 float x, r, x_ref, x1;
 i=0;
 i1=0;
 i2=0;
 printf("Digite o valor inicial, entre 0 e 1: \n");
 scanf("%f",&x);
 printf("Digite o valor de r, entre 0 e 4: \n");
 scanf("%f",&r);
 printf ("x inicial: %f;\nValor de r: %f.\n", x, r);
 if ((r>=0) && (r<=4) && (x>=0) && (x<=1))
 {
  fprintf (f1, "%f\n", x);
  fprintf (f1, "%f\n", r);
  while (i<=999)
  {
   x=x*r*(1-x);
   i=i+1;
  }
  x_ref=x;
  x1=x;
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
  fprintf (f1, "%d\n", soma);
  printf("Há %d valor(es).\n NOTA: se forem mais de 64 valores, os restantes não foram considerados...\n", soma);

// Vou repetir o ciclo de todos os valores de estabilizção porque no exercício 4 dá jeito a soma estar antes deles (por isso, tenho de fazer o ciclo dos valores de estabilização outra vez, para pô-los, AGORA, no ficheiro

  while (i2<=63)
  {
   x1=x1*r*(1-x1);
   fprintf(f1, "%f\n", x1);
   i2=i2+1;
   if (x1==x_ref)
   {
    break;
   }
  }
 }
 else
 {
  printf ("Valor(es) inválido(s).\n");
 }
 fclose (f1);
 return 0;
}
