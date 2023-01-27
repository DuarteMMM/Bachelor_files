/******************************************************
 *                Física Computacional                *
 *                    Exercício 28                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include "Exercicio28.h"
#include <iostream>
#include <string>
using namespace std;

int main (){
  cout << "\n----- Exercício 28 -----\n" << endl;

  // Testar a alínea b
  cout << "Alínea b\n" << endl;
  pessoa P[10]; // É chamado o default constructor

  cout << "\n--------------------------\n" << endl;

  // Ir-se-á dar uso das funções feitas para ter informações de 3 pessoas
  
  pessoa Duarte; // constructor com os valores default
  Duarte.Print();

  pessoa Oscar ("Oscar", 10); // constructor com valores específicos
  Oscar.Print();

  pessoa Vanessa; // Usar-se-ão os "Set"
  Vanessa.SetName ("Vanessa");
  Vanessa.SetBornDate (15);
  
  // Usar os "Get"
  string nome = Vanessa.GetName();
  unsigned int data = Vanessa.GetBornDate();
  cout << "\nA pessoa " << nome << " nasceu no dia " << data << ".\n" << endl;

  // Ponteiro para ponteiros
  cout << "--------------------------\n" << endl;
  cout << "Obter informações com a função DoArray:\n" << endl;
  pessoa **p;
  p = DoArray (3);
  p[0] = &Duarte;
  p[1] = &Oscar;
  p[2] = &Vanessa;
  
  (*p[0]).Print();
  (*p[1]).Print();
  (*p[2]).Print();

  // Limpar
  nome.clear();
  cout << " -FIM-\n" << endl;
  
  return 0;
}
