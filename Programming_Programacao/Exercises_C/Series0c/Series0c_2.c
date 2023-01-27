#include <stdio.h>
int main()
{
 int i1, i2, i3, i4;
 FILE *f1;
 f1=fopen("tabuada","rt");
 for (i1=0; i1<11; ++i1)
 {
  fscanf(f1,"%d x %d = %d\n", &i2, &i3, &i4);
  printf("%d x %d = %d\n", i2, i3, i4);
 }
 fclose(f1);
 return 0;
}
