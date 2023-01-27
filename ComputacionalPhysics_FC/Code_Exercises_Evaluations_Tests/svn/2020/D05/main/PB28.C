#include "pessoa.h"


pessoa** DoArray(int N) {

  pessoa** a = new pessoa* [N];

  for (int i = 0; i < N; i++) {

    a[i] = new pessoa("foo", i);

  }

  return a;
}


int main() {

  pessoa P[10];
  int x = 5;

  pessoa** turma = DoArray(x);

  for (int i = 0; i < x; i++) {

    delete turma[i];

  }
    
  delete[] turma;
  
  return 0;
}
