#include "Exercicio28.h"
#include <cstdio> // printf
#include <iostream> // cout
#include <string> // classe string
using namespace std;

// Default constructor
pessoa::pessoa (string name_a, unsigned int DataN_a) : name(name_a), DataN(DataN_a) {
  printf ("[%s] constructor called...\n", __PRETTY_FUNCTION__);
}

void pessoa::SetName (string name_a){
  printf ("[%s] SetName called...\n", __PRETTY_FUNCTION__);
  name = name_a;
}

void pessoa::SetBornDate (unsigned int DataN_a){
  printf ("[%s] SetBornDate called...\n", __PRETTY_FUNCTION__);
  DataN = DataN_a;
}
  
string pessoa::GetName() const{
  printf ("[%s] GetName called...\n", __PRETTY_FUNCTION__);
  return name;
}

unsigned int pessoa::GetBornDate() const{
  printf ("[%s] GetBornDate called...\n", __PRETTY_FUNCTION__);
  return DataN;
}

void pessoa::Print (){
  printf ("[%s] Print called...\n", __PRETTY_FUNCTION__);
  cout << "\nA pessoa " << name << " nasceu no dia " << DataN << ".\n" << endl;
}

pessoa** DoArray (int N){
  printf ("[%s] DoArray called...\n", __PRETTY_FUNCTION__);
  pessoa **p;
  p = new pessoa *[N];
  return p;
}
