#ifndef __alunoIST__
#define __alunoIST__
#include <string>
#include "Exercicio28.h"
using namespace std;

class alunoIST : public pessoa{

	public:
	int number;
	string curso;
	alunoIST (int number_a = 96523, string curso_a = "MEFT");
	~alunoIST()=default;
	void SetNumber (int);
	void SetCurso (string);
	int GetNumber() const;
	string GetCurso() const;
	void Print();
	
	// Tive de por isto em public devido ao exercício 30 (que exigia vir aqui buscar coisas)
	//private:
	//int number;
	//string curso;
};

void Dummy (pessoa**, const int); // int has the number of array entries

#endif

