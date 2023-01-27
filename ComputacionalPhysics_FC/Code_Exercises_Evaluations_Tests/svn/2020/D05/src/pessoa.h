//classe pessoa
#ifndef __PESSOA__
#define __PESSOA__

#include <string>

using namespace std;

class pessoa {

protected:

  string nome;

  unsigned int DataN;


public:

  //constructor (nome do aluno, data de nascimento)
  pessoa(string = "", unsigned int = 0);

  ~pessoa();

  void SetName(string); //set name

  void SetBornDate (unsigned int); //nascimento

  string GetName(); //get name

  unsigned int GetBornDate();

  virtual void Print(); //print

};

#endif
