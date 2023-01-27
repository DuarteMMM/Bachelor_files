#ifndef __pessoa__
#define __pessoa__
#include <string>
#include <cstdio>
using namespace std;

class pessoa{

public:
//constructor (nome do aluno, data de nascimento)

	pessoa (string name_a = "Duarte", unsigned int DataN_a = 20);
	~pessoa ()=default;
	void SetName (string); // definir o name
	void SetBornDate (unsigned int); // definir o dia de nascimento
	string GetName() const; // obter o name
	unsigned int GetBornDate() const; // obter a data
	virtual void Print(); // print do nome e data

private:
	string name; // nome
	unsigned int DataN; // data de nascimento
};

pessoa** DoArray (int);
	
#endif
