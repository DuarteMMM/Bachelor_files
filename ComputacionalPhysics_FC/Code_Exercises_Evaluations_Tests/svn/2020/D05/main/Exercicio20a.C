/******************************************************
 *                Física Computacional                *
 *                   Exercício 20a                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream>
#include <cstdio>
using namespace std;

int main ()
{
  printf ("\n-=-=-=-=-=- Lambda functions -=-=-=-=-=-\n\n");

  printf ("Digite o nível de energia do átomo de H: \n");
  int n, teste_n, Z=1;

  teste_n = scanf ("%d", &n);
  if ( (teste_n != 1) || (n < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }

  // Nota: Nas lambda functions, tem de se declarar como auto; o "-> double" é desnecessário, mas indica que a function retorna um double
  
  auto fE = [Z] (int n) -> double
	    {
	      double k = 2.179e-18;
	      double En = (-k*Z*Z)/(n*n);
	      return En;
	    };
  // Nota: Vi na net que a fórmula pode ser simplificada para ter este k

  cout << "\nPara n=" << n << ": E = " << fE (n) << " J\n" << endl;
  cout << "Em eV: E = " << (fE (n))/(1.602176565e-19) << " eV\n" << endl;

  return 0;
}
	    
	       
