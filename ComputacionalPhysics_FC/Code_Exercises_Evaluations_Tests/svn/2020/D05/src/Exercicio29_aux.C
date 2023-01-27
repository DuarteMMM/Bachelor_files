#include "Exercicio29.h"
#include <iostream>
using namespace std;

// Constructor
alunoIST::alunoIST (int number_a, string curso_a) : number(number_a), curso(curso_a) {
  printf ("[%s] constructor called...\n", __PRETTY_FUNCTION__);
}

void alunoIST::SetNumber (int number_a){
  printf ("[%s] SetNumber called...\n", __PRETTY_FUNCTION__);
  number = number_a;
}

void alunoIST::SetCurso (string curso_a){
  printf ("[%s] SetCurso called...\n", __PRETTY_FUNCTION__);
  curso = curso_a;
}
  
int alunoIST::GetNumber() const{
  printf ("[%s] GetNumber called...\n", __PRETTY_FUNCTION__);
  return number;
}

string alunoIST::GetCurso() const{
  printf ("[%s] GetCurso called...\n", __PRETTY_FUNCTION__);
  return curso;
}

void alunoIST::Print (){
  printf ("[%s] Print called...\n", __PRETTY_FUNCTION__);
  cout << "\nO aluno " << number << " é do curso " << curso << ".\n" << endl;
}

void Dummy (pessoa** p, const int n){
  printf ("[%s] Dummy called...\n\n", __PRETTY_FUNCTION__);
  int contador=0;
  while (contador<n)
    {
      (*p[contador]).Print();
      contador++;
    }
}
		    
