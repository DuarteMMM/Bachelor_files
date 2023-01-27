#include <stdio.h>
int main()
{
 int a, b, d;
 FILE *f1;
 f1=fopen ("tabuada","wt"); 
 b=0;
 printf ("Digite o valor cuja tabuada deseja saber: \n");
 scanf ("%d", &a);
 if (a<=0)
 {
  printf("Digitou um valor inválido.\n");
       return 1;
 }
 else
 {
  while (b<=10)
  {
   d=a*b;
   printf("%d x %d = %d\n", a, b, d);
   fprintf(f1, "%d x %d = %d\n", a, b, d);
   b=b+1;
  }
 }
 fclose (f1);
 return 0;
}
