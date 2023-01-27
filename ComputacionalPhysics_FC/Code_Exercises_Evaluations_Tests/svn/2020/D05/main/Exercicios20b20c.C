/******************************************************
 *                Física Computacional                *
 *                Exercícios 20c e 20b                *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio>
#include <iostream>
using namespace std;

int main ()
{
  printf ("\n-=-=-=-=-=- Transições entre níveis de energia -=-=-=-=-=-\n\n");

  int n_inicial, n_final, teste_n_inicial, teste_n_final, Z, teste_Z, n;
  double k = 2.179e-18;
  double h = 6.626070043e-34; // Constante de Planck
  double c = 299792458; // Velocidade da luz

  printf ("Digite o valor de Z: ");

  teste_Z = scanf ("%d", &Z);
  if ( (teste_Z != 1) || (Z < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }

  printf ("\nDigite o nível de energia inicial: ");
  
  teste_n_inicial = scanf ("%d", &n_inicial);
  if ( (teste_n_inicial != 1) || (n_inicial < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 2;
    }

  printf ("\nDigite o nível de energia final: ");
  
  teste_n_final = scanf ("%d", &n_final);
  if ( (teste_n_final != 1) || (n_final < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 3;
    }

  n = n_final-n_inicial;
  
  auto fEL = [k, c, h] (int n, int Z) -> double
	     {
	       double EnL = (h*c) / ((k*Z*Z)/(n*n));
	       return EnL;
	     };
  
  // Nota: Partindo de E=hf, obtém-se a equação para lambda

  cout << "\n\nPara esta transição, Lambda = " << fEL (n, Z) << " m\n" << endl;

  return 0;
}	       
