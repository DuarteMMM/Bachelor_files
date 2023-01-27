/******************************************************
 *                Física Computacional                *
 *                    Exercício 29                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "Exercicio28.h"
#include "Exercicio29.h"
#include <iostream>
#include <string>
using namespace std;

int main(){

  // Alínea b - criar um array qualquer de objetos alunoIST com conteúdo...
  cout << "\n-=-=-=- Exercício 29 -=-=-=-\n\n----- Alínea b -----\n\n";
  
  alunoIST A[3];
  cout << endl;
  alunoIST Duarte1;
  A[0] = Duarte1;
  A[0].Print();
  alunoIST Maria (96777, "LMAC");
  A[1] = Maria;
  A[1].Print();
  alunoIST Miguel;
  Miguel.SetNumber (95420);
  Miguel.SetCurso ("MEFT");
  int nr = Miguel.GetNumber();
  string cur = Miguel.GetCurso();
  A[2] = Miguel;
  cout << "\nO aluno " << nr << " é do curso " << cur << ".\n";

  // Alínea c

  cout << "\n----- Alínea c -----\n" << endl;
  // Criar (3)  objetos pessoa e os arrays pedidos
  pessoa Duarte2;
  pessoa Oscar ("Oscar", 10);
  pessoa Vanessa ("Vanessa", 15);
  pessoa **p;
  p = DoArray (3);
  cout << endl;
  p[0] = &Duarte2;
  p[1] = &Oscar;
  p[2] = &Vanessa;
  Dummy(p, 3);

  // Resposta: É chamada a função Print() da classe "pessoa"

  delete []p;
  cur.clear();
  cout << " -FIM-\n";
  return 0;
}
