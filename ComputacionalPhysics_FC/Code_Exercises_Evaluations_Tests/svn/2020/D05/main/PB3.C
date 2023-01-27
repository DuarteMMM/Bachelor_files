#include <cstdio>
#include <cmath>



int main() {

  int vint[2];
  long dif = &vint[1] - &vint[0] ;

  printf("%p , %p\n", &vint[1], &vint[0]);
  printf("Size of double: %li\n", dif);

  
  return 0;

}
