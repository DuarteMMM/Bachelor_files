#include "pessoa.h"
#include <iostream>

using namespace std;

pessoa::pessoa(string arg_nome, unsigned int arg_data) : nome(arg_nome), DataN(arg_data) {
  cout << "pessoa::constructor called" << endl;
}


pessoa::~pessoa() {
  cout << "pessoa::destructor called" << endl;
}

void pessoa::SetName(string name) {
  cout << "pessoa::SetName called" << endl;
  nome = name;
}


void pessoa::SetBornDate (unsigned int data) {
  cout << "pessoa::SetBornDate called" << endl;
  DataN = data;
}


string pessoa::GetName() {

  cout << "pessoa::GetName called" << endl;
  return nome;

}


unsigned int pessoa::GetBornDate() {

  cout << "pessoa::GetBornDate called" << endl;
  return DataN;

}


void pessoa::Print() {

  cout << "pessoa::Print called" << endl;
  cout << "Nome: " << nome << ", Data de Nascimento: " << DataN << endl;

}
