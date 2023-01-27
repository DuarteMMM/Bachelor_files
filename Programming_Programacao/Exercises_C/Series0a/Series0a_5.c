# include <stdio.h>
int main ()
{
  int a, b, c, teste;
  printf ("Qual o número cuja tabuada deseja saber?\n");
  teste = scanf ("%d", &a);
  b = 0;
  if (teste != 1)
    {
      printf ("Inseriu algo inválido.\n");
      return 1;
    }
  while (b<=10)
    {
      c=a*b;
      printf ("%dx%d=%d\n", a, b, c);
      b+=1;
    }
  return 0;
}
    
