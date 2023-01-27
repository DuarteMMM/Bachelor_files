/******************************************************
 *                Física Computacional                *
 *                     Exercício 23                   *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;


int main ()
{
  printf ("\n-=-=-=-=- Containers STL -=-=-=-=-\n");
  vector<int>a(9);
  a={3,2,1,6,5,4,9,8,7};
  vector<int>b(9);
  b={10,12,15,18,24,32,40,45,50};

  // Alínea a
  
  vector<int>aa(9);
  int contador = 0, acrescimo=10, contador1 = 0, contador_b=0;
  printf ("\nValores do vetor aa:   ");
  while (contador < 9)
    {
      if (a[contador] % 2 == 0)
	aa[contador] = a[contador];
      else
	aa[contador] = 2*a[contador];

      cout << aa[contador]<< "   ";
      contador++;
    }
  contador = 0;

  // Alínea b

  vector<int>c (9);
  copy (a.begin(), a.begin()+9, c.begin()); // Copiar os valores de a, embora seja um pouco irrelevante, porque eles vão ser apagados pelos valores de b que se vão metendo em c
  while (contador1 < 9)
    {
      while (contador < 9)
	{
	  if ( (b[contador] % a[contador1]) == 0)
	    {
	      c.resize (acrescimo); // Mudar tamanho de c
	      copy_n (b.begin()+contador, 1, c.begin()+1+contador_b); // Colocar o valor de b na posição certa de c
	      acrescimo++; // Para novo resize
	      contador_b++; // Para colocar o novo valor de b
	    }
	  contador++;
	}
      contador=0;
      contador1++;
      copy_n (a.begin()+contador1, 1, c.begin()+1+contador_b); // Porque colocar os sucessivos valores de b depois 
      contador_b++; // Porque se colocou o valor de a
    }
  contador = 0;

  printf ("\n\nValores do vetor c:    ");
  while (contador < (acrescimo-1))
    {
      cout << c[contador] << "   ";
      contador++;
    }
  contador = 0;
  
  // Alínea c: ordenar por ordem crescente
  
  sort (c.begin(), c.end());
  printf ("\n\nValores do vetor c (ordem crescente):    ");
  while (contador < (acrescimo-1))
    {
      cout << c[contador] << "   ";
      contador++;
    }
  contador = 0;

  // Alínea d: construir em ordem decrescente
  /* Nota: diz "constuir" no enunciado; poderia sempre escrever num novo vetor os valores de c nesta nova ordem, a partir do c ordenado na alínea c; porém, usa-se aqui a função específica, embora não sei se isso é considerado "construir"... Porém, é mais prático.*/

  sort (c.begin(), c.end(), [] (int a,int b) {return a>b;});
  printf ("\n\nValores do vetor c (ordem decrescente):  ");
  while (contador < (acrescimo-1))
    {
      cout << c[contador] << "   ";
      contador++;
    }

  printf ("\n\n -FIM-");
  printf ("\n\n");
  a.clear();
  b.clear();
  aa.clear();
  c.clear();
  
  return 0;
}
