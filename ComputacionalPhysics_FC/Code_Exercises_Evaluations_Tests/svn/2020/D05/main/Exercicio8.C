/******************************************************
 *                Física Computacional                *
 *                    Exercício 7                     *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

/*Para compilar:

Criar .o através de .C:
g++ -std=c++11 -C Exercicio8.C

Criar .exe através de .o:
g++ -std=c++11 Exercicio8.o -o Exercicio8.exe

Realizando os dois comandos em simultâneo (embora não fique guardado o ficheiro .o):
g++ -std=c++11 Exercicio8.C -o Exercicio8.exe
*/

#include <iostream> // std::cout
#include <cstdio> // scanf

using namespace std;

int fatorial (int n)
{
  int resultado, contador;
  contador = n;
  resultado = 1;

  while (contador > 0)
    {
      resultado = resultado*contador;
      contador -= 1;
    }

  return resultado;
}
  

int main () {
  int n, teste_n, fatorial_n;
  
  cout << "\n-=-=-=-=-=- Fatorial de um número-=-=-=-=-=-\n" << endl;
  cout << "Digite um número inteiro positivo ou nulo: ";
  
  teste_n = scanf ("%d", &n);

  if ( (teste_n!=1) || (n<0) )
    {
      cout << "\nERRO: Digitou algo inválido.\n" << endl;
      return 1;
    }

  fatorial_n = fatorial (n);

  cout << "\nO valor do fatorial de " << n << " é " << fatorial_n << ".\n" << endl;

  return 0;
}
