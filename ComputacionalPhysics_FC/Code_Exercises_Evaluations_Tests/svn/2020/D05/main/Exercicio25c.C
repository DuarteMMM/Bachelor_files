/******************************************************
 *                Física Computacional                *
 *                    Exercício 25c                   *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "./Exercicio25.h"
#include <vector>
#include <iostream>
#include <map>
using namespace std;

int main ()
{
  cout << "\n-=-=-=-=-=- The first 6 elements of the Periodic Table (alínea c)-=-=-=-=-=-" << endl;
  
  // Hydrogen

  ATOM hydrogen;
  hydrogen.A = 1;
  hydrogen.Z = 1;
  hydrogen.mass = 938.89;
  hydrogen.name = "Hydrogen";

  // Helium

  ATOM helium;
  helium.A = 4;
  helium.Z = 2;
  helium.mass = 3728.40;
  helium.name = "Helium";

  // Lithium

  ATOM lithium;
  lithium.A = 7;
  lithium.Z = 3;
  lithium.mass = 6465.50;
  lithium.name = "Lithium";

  // Berilium

  ATOM berilium;
  berilium.A = 9;
  berilium.Z = 4;
  berilium.mass = 8394.79;
  berilium.name = "Berilium";

  // Boron

  ATOM boron;
  boron.A = 11;
  boron.Z = 5;
  boron.mass = 10070.38;
  boron.name = "Boron";

  // Carbon

  ATOM carbon;
  carbon.A = 12;
  carbon.Z = 6;
  carbon.mass = 11187.90;
  carbon.name = "Carbon";

  map< string, ATOM > mperiodic; // A string é a "key" para o elemento ATOM
  mperiodic ["Hidrogénio"] = hydrogen;
  mperiodic ["Hélio"] = helium;
  mperiodic ["Lítio"] = lithium;
  mperiodic ["Berílio"] = berilium;
  mperiodic ["Boro"] = boron;
  mperiodic ["Carbono"] = carbon;

  // Também se poderia ter feito: map< string, ATOM> mperiodic{ {"Hidrogénio", hydrogen}, {"Hélio", helium}, {"Lítio", lithium}, {"Berílio", berilium}, {"Boro", boron}, {"Carbono", carbon}};

  map< string, ATOM>::iterator it;
  for(it=mperiodic.begin(); it!=mperiodic.end();++it)
    {
      cout << "\n*" << it->second.name << "*" << endl;
      cout << "Atomic number:  " << it->second.Z << endl;
      cout << "Number of mass: " << it->second.A << endl;
      cout << "Mass in MeV:    " << it->second.mass << endl;
    }
  
  // Não consegui fazer com que não fossem dados os elementos por ordem não alfabética...

  mperiodic.clear(); // Limpar o mapa
  cout << endl;

  return 0;
}
