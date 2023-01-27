#include "Material.h"
#include <iostream>


using namespace std;


Material::Material(string fname, Double_t fdens) : name(fname), density(fdens) {;}

//Default Destructor


string Material::GetName() {

  return name;
  
}


Double_t Material::GetDensity() {

  return density;

}


void Material::Print() {

  cout << "Nome: " << name << "; Densidade: " << density << endl;

}
