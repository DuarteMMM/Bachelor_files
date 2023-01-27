/******************************************************
 *                Física Computacional                *
 *                    Exercício 25a                   *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "./Exercicio25.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main ()
{
  cout << "\n-=-=-=-=-=- The first 6 elements of the Periodic Table (alínea a)-=-=-=-=-=-" << endl;
  
  // Hydrogen

  ATOM hydrogen;
  hydrogen.A = 1;
  hydrogen.Z = 1;
  hydrogen.mass = 938.89;
  hydrogen.name = "Hydrogen";

  /*Como calcular a massa em unidades MeV: ver o link 'https://en.wikipedia.org/wiki/Electronvolt' com a definição desta unidade; pesquisando na net as massas dos átomos em kg, facilmente se converterá para  MeV.*/

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

  vector<ATOM> vperiodic(6);
  vperiodic = {hydrogen, helium, lithium, berilium, boron, carbon};
  
  for_each (vperiodic.begin(), vperiodic.end(), [](ATOM var){
						  cout << "\n*" << var.name << "*" << endl;
						  cout << "Atomic number:  " << var.Z << endl;
						  cout << "Number of mass: " << var.A << endl;
						  cout << "Mass in MeV:    " << var.mass << endl;
						});
  vperiodic.clear();
  cout << endl;
  
  return 0;
}
