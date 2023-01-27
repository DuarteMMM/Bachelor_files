/******************************************************
 *                Física Computacional                *
 *                    Exercício 12                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio> // scanf, printf
#include <iostream> // cout
#include <cmath> // sqrt
using namespace std;

int main ()
{
  printf ("\n-=-=-=- Massa que cai de altura h -=-=-=-\n\n");
  double altura, tempo;
  int teste_altura;

  cout << "Digite o valor da altura h: ";
  teste_altura = scanf ("%lf", &altura);

  if ( (teste_altura != 1) || (altura < 0.00000000001) )
    {
      cout << "\nDigitou um valor inválido para a altura.\n" << endl;
      return 1;
    }

  tempo = sqrt ( (2*altura) / 9.81 );

  printf ("\nA massa demora (aproximadamente) %.3lf segundos a chegar ao solo.\n\n", tempo);

  return 0;
}
  
/* Resposta à alínea b:
   De uma altura de 100 metros, a massa demora, aproximadamente, 4.515 segundos a chegar ao solo. */

  
