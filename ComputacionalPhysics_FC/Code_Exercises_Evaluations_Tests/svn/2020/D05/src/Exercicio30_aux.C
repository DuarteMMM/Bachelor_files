#include "Exercicio30.h"
#include <cstdio>
#include <string>
using namespace std;

Turma::Turma (string nome_a, alunoIST** va_a, int Nalunos_a){
  printf ("[%s] default constructor called...\n", __PRETTY_FUNCTION__);
  nome = nome_a;
  va = va_a;
  Nalunos = Nalunos_a;
}
/*
// Escrevi um destrutor específico porque é aconselhado quando a classe tem ponteiro(s) como variável(eis); neste caso, tem! Mas não consegui...
Turma::~Turma(){
  printf ("[%s] destructor called...\n", __PRETTY_FUNCTION__);
  delete[]va;
  }*/

Turma::Turma(const Turma& otherTurma) : nome(otherTurma.nome), va(otherTurma.va), Nalunos(otherTurma.Nalunos) {
  printf ("[%s] copy constructor called...\n", __PRETTY_FUNCTION__);
}

const Turma& Turma::operator= (const Turma& otherTurma) {
  printf ("[%s] copy assignment called...\n", __PRETTY_FUNCTION__);
  
  if (this != &otherTurma) {
    nome = otherTurma.nome;
    va = otherTurma.va;
    Nalunos = otherTurma.Nalunos;
  }

  return *this;
}

void Turma::AddAluno (alunoIST* const individuo){
  printf ("[%s] AddAluno called...\n", __PRETTY_FUNCTION__);
  Nalunos++;
  alunoIST **novo_va;
  novo_va = new alunoIST *[Nalunos];
  int contador=0;
  while (contador < Nalunos-1)
    {
      novo_va[contador] = va[contador];
      contador++;
    }
  novo_va[Nalunos-1] = individuo;
  va = novo_va;
}

alunoIST* Turma::FindAluno (int numero)
{
  printf ("[%s] FindAluno called...\n", __PRETTY_FUNCTION__);
  int contador=0;
  while (contador<Nalunos)
    {
      if (va[contador]->number == numero)
	{
	  return va[contador];
	  break;
	}
      else
	contador++;
    }
  return nullptr;
}

int Turma::GetNalunos(){
  printf ("[%s] GetNalunos called...\n", __PRETTY_FUNCTION__);
  return Nalunos;
}
