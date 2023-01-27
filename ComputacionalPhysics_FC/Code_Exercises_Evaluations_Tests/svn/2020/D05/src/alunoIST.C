#include "alunoIST.h"
#include <iostream>

alunoIST::alunoIST(int arg_number, string arg_branch): number(arg_number), branch(arg_branch) {
  cout << "alunoIST::constructor called" << endl;
}


alunoIST::~alunoIST() {
  cout << "alunoIST::destructor called" << endl;
}


void alunoIST::SetNumber(int arg_number) {

  number = arg_number;

}


int alunoIST::GetNumber() {

  return number;

}


void alunoIST::SetBranch(string curso) {

  branch = curso;

}


string alunoIST::GetBranch() {

  return branch;

}


void alunoIST::Print() {

  pessoa::Print();
  cout << "Aluno número: " << number << ", curso: " << branch << endl;
  
}
