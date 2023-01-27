#ifndef __turma__
#define __turma__endif
#include "Exercicio29.h"
#include <string>

class Turma{
	public:
	Turma (string nome_a = "MEFT Turma 1", alunoIST** = nullptr, int Nalunos_a = 25); // Default constructor
	~Turma()=default; // destructor
	
	Turma (const Turma& otherTurma); // Copy constructor
	
	const Turma& operator= (const Turma& otherTurma);
	
	void AddAluno (alunoIST* const);
	alunoIST* FindAluno (int numero);
	int GetNalunos();
		
	private:
	string nome; // Adicionei, porque o exercício queria nome, mas se não houver alunoIST** também no constructor, acho que não faz muito sentido...
	alunoIST **va; // pointer para array de ponteiros de objetos
	int Nalunos;
};

#endif
