/******************************************************
 *                Física Computacional                *
 *                    Exercício 17                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int* func1 ()
{
  int *aleatorio1;
  int a;
  a = rand();
  printf ("\nO valor aleatório gerado na primeira função é: %d", a);
  aleatorio1=&a;
  return aleatorio1;
}

int& func2 ()
{
  int aleatorio = rand();
  int& a = aleatorio;
  cout << "O endereço no interior da segunda função é: "<< (&a) << endl;
  cout << "O valor aleatório gerado na segunda função é: " << a << endl;
  return a;
}

int main ()
{
  srand (time (NULL));
  //int contador = 0;

  //while (contador < 10e+6)
  //{
  int *aleatorio1 = func1 (); // func1
  printf ("\nO valor aleatório retornado da primeira função é: %d\n\n", *aleatorio1);

  int& aleatorio2 = func2 (); // Endereço da func2
  int valor = aleatorio2; // Valor da func2
  cout << "O endereço retornado da segunda função é: " << (&aleatorio2) << endl;
  cout << "O valor aleatório retornado da segunda função é: " << valor << "\n" << endl;

  // contador++;
  //}

  return 0;
}

// Resposta à alínea c: verificou-se que não existe memory leakage (fez-se comentários nos prints e couts (para que o programa execute 10e+6 vezes mais rapidamente) e o programa foi executado corretamente).
// Da maneira que se resolveu o exercício, não foi necessário limpar memória.
