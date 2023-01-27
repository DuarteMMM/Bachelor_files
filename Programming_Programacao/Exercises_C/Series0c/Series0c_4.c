#include <stdio.h>
int main()
{
 float x, r, x1;
 int soma, i1, total;
 i1=0;
 total=0;
 FILE *f1;
 f1 = fopen ("órbitas Malthus", "rt");
 printf("Valores de x inicial, r e período, respetivamente: \n");
 fscanf (f1, "%f\n", &x);
 printf ("%f     ", x);
 fscanf (f1, "%f\n", &r);
 printf ("%f     ", r);
 fscanf (f1, "%d\n", &soma);
 printf ("%d\n\n", soma);
 printf ("Valor(es) da órbita:\n");
 while (i1<soma)
 {
  fscanf (f1, "%f\n", &x1);
  total=total + 1;
  i1=i1+1;
  printf ("%f     ", x1);
  if ((total%3)==0)
  {
   printf("\n");
  }
 }
 printf("\n");
 fclose (f1);
 return 0;
}
