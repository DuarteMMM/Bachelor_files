#ifndef __ALUNOIST__
#define __ALUNOIST__

#include <pessoa.h>
#include <string>

using namespace std;

class alunoIST : public pessoa {

 private:
  
  int number;
  
  string branch;

 public:

  
  //constructor (numero e nome do aluno)
  alunoIST(int, string);


  ~alunoIST();


  void SetNumber(int);


  int GetNumber();


  void SetBranch(string);


  string GetBranch();


  void Print();


};


#endif
