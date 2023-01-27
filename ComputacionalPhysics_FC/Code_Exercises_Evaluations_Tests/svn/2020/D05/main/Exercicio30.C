/******************************************************
 *                Física Computacional                *
 *                    Exercício 30                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "Exercicio30.h"
#include <iostream>
using namespace std;

int main()
{
  cout << "\n-=-=-=- Exercício 30 -=-=-=-\n\n";

  cout << "---> Criar 3 alunos...\n" << endl;
  alunoIST* a;
  alunoIST Duarte;
  a = &Duarte;
  Duarte.Print();
  alunoIST* b;
  alunoIST Maria (96324, "LMAC");
  alunoIST Joana(Maria); // Apenas para testar o copy constructor
  alunoIST Ana=Maria; // Apenas para testar o operador =
  b = &Maria;
  Maria.Print();
  alunoIST* c;
  alunoIST Sara;
  c = &Sara;
  Sara.Print();

  cout << "---> Juntar os alunos na 'turma'\n" << endl;

  alunoIST** total = new alunoIST*[3];
  total[0]=a;
  total[1]=b;
  total[2]=c;
  Turma turma ("MEFT T21", total, 3);

  cout << "\n---> Criar um quarto aluno e adicioná-lo à turma\n" << endl;

  alunoIST* d;
  alunoIST Francisco (96123, "MEFT");
  d = (&Francisco);
  Francisco.Print();
  turma.AddAluno(d);

  cout << "\n---> Ler o número do aluno adicionado\n" << endl;
  
  alunoIST* e;
  e = turma.FindAluno (96123);
  cout << "\n" << e->number; // Para verificar que foi encontrado corretamente

  cout << "\n\n---> Retornar o número de alunos da turma\n" << endl;
  
  int numero = turma.GetNalunos();
  cout << "\n" << numero;

  cout << "\n\n-FIM-\n";
  return 0;
}
