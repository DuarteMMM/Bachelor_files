/******************************************************
 *                Física Computacional                *
 *                     Exercício 22                   *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

vector<int> array2vec (int n, const int* array)
{
  vector<int>vec (&array[0], &array[0]+n);
  return vec;
}

vector<int> array2vecsort (int n, const int* array, int o)
{
  vector<int>vec (&array[0], &array[0]+n);

  // Ordenar por ordem crescente
  if (o == 0)
    sort (vec.begin(), vec.end());

  // Ordenar por ordem descrescente
  if (o == 1)
    sort (vec.begin(), vec.end(), [] (int a,int b) {return a>b;});

  return vec;
}

int array2vecmax (int n, const int* array)
{
  vector<int>vec (&array[0], &array[0]+n);
  int max = *(max_element (vec.begin(), vec.end()));
  return max;
}

int array2vecfind (int n, const int* array, int value)
{
  vector<int>vec (&array[0], &array[0]+n);
  vector<int>::iterator it = find (vec.begin(), vec.end(), value);
  int pos;
  // Valor não se encontra no array (o find retorna ponteiro para o fim do array)
  if (it == vec.end())
    pos = 0;
  // Valor encontra-se no array
  else
    pos = it-vec.begin()+1;
  return pos;
}


int main ()
{
  int n, teste_n, contador=0, teste_valor, o, teste_o, maximo, pos;
  printf ("\n-=-=-=-=-=- Tranferir array para vetor STL -=-=-=-=-=-\n");
  printf ("\nQuantos elementos deseja que o vetor tenha? ");
  teste_n = scanf ("%d", &n);
  if ( (teste_n != 1) || (n < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }

  int* array = (int*) malloc (n*sizeof (int));
  vector<int>v (n);

  printf ("\n");
  while (contador < n)
    {
      printf ("Valor inteiro para o array: ");
      teste_valor = scanf ("%d", &array[contador]);
      if (teste_valor != 1)
	{
	  printf ("\nDigitou algo inválido.\n\n");
	  return 2;
	}
      contador++;
    }

  contador = 0;

  // Transferir o array para vetor STL (alínea a)
  
  v = array2vec (n, array);

  // Ordenar por ordem crescente e decrescente (alínea b)

  printf ("\nDeseja ordenar o vetor por ordem crescente (0) ou decrescente (1)? ");
  teste_o = scanf ("%d", &o);
  if ( (teste_o  != 1) || (o < 0) || (o > 1) )
    {
      printf ("\nDigitou algo inválido. Deve escrever 0 ou 1.\n\n");
      return 3;
    }

  v = array2vecsort (n, array, o);

  printf ("\nResultado da ordenação: ");

  while (contador < n)
    {
      cout << v[contador] << "   ";
      contador++;
    }

  // Valor máximo

  maximo = array2vecmax (n, array);
  printf ("\n\nO valor máximo deste vetor é %d.\n", maximo);

  // Posição do valor 7

  pos = array2vecfind (n, array, 7);
  if (pos == 0)
    printf ("\nO valor 7 não se encontra no array.");
  else
    printf ("\nO valor 7 está na posição %d do vetor (não ordenado).", pos);
  

  printf ("\n\n");
  
  free (array);
  v.clear();

  return 0;
}

/* Experimentei para os vetores a e b dados no enunciado, fazendo print de "array" e "v": verifiquei que tinham os mesmos elementos (programa bem sucedido) */
