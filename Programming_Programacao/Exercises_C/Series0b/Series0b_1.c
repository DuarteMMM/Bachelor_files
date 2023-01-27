# include <stdio.h>
# include <math.h>
int main()
{
  float a, b, c, delta, x1, x2, x3;
  printf ("Resolução de equações do 2ºgrau!\n");
  printf ("Digite o valor de a:\n");
  scanf ("%f", &a);
  printf ("Digite o valor de b:\n");
  scanf ("%f", &b);
  printf ("Digite o valor de c:\n");
  scanf ("%f", &c);
  delta = (b*b)-4*a*c;
  printf ("%f\n", delta);
  if (delta>0)
    {
      x1 = (-b+sqrt(delta))/(2*a);
      x2 = (-b-sqrt(delta))/(2*a);
      printf ("As soluções são reais e elas são: %f e %f.\n", x1, x2);
    }
  if (delta==0)
    {
      x1 = (-b)/(4*a*c);
      printf ("A solução única (raiz dupla) é %F.\n", x1);
    }
  if (delta<0)
    {
      x1 = (-b)/(2*a);
      x2 = sqrt (-delta)/(2*a);
      x3 = -x2;
      printf ("As soluções (imaginárias) são: %f+(%f) i e %f+(%f)i.\n", x1, x2, x1, x3);
    }
  return 0;
}

  
