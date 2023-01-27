#include <stdio.h>
int main ()
{
  int a, b, c;
  a=6;
  b=0;
  while (b<=10)
    {
      c=a*b;
      printf ("6 x %d = %d\n", b, c);
      b=b+1;
    }
  return 0;
}
