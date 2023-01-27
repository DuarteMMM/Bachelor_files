/******************************************************
 *                Física Computacional                *
 *                    Exercício 26                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm> // copy
#include <map>
#include <string>
using namespace std;

vector<vector<int>>GetMatrix (int nrows, int ncols, int**M, vector<vector<int>> matriz)
{
  int contador_linhas=0;
  while (contador_linhas < nrows)
    {
      copy (&M[contador_linhas][0], &M[contador_linhas][0]+ncols, matriz[contador_linhas].begin());
      contador_linhas++;
    }
  return matriz;
}

vector<vector<int>>Mmapfind (string c,  map< string,  vector<vector<int>>> Mmap)
{
  vector<vector<int>>matriz = Mmap.find (c)->second;
  return matriz;
}


int main ()
{
  cout << "\n-=-=-=-=-=- Exercício 25 -=-=-=-=-=-\n" << endl;
  
  int** a = (int**) malloc (2*sizeof(int*));
  a [0] = (int*) malloc (3*sizeof(int));
  a [0][0] = 2;
  a [0][1] = 10;
  a [0][2] = 5;
  a [1] = (int*) malloc (3*sizeof(int));
  a [1][0] = 3;
  a [1][1] = 2;
  a [1][2] = 7;
  vector<int>linha0_a (3);
  vector<int>linha1_a (3);
  vector<vector<int>>matriz_a = {linha0_a, linha1_a};
  matriz_a=GetMatrix (2, 3, a, matriz_a);
  cout << "Matriz A" << endl;
  for(int i_a = 0 ; i_a < matriz_a.size(); i_a++)
    {
      for (int j_a = 0 ; j_a < matriz_a[i_a].size() ; j_a++)
	printf ("%2d ", matriz_a[i_a][j_a]);
      cout << endl;
    }
  
  int** b = (int**) malloc (3*sizeof(int*));
  b [0] = (int*) malloc (3*sizeof(int));
  b [0][0] = 5;
  b [0][1] = 1;
  b [0][2] = 3;
  b [1] = (int*) malloc (3*sizeof(int));
  b [1][0] = 10;
  b [1][1] = 1;
  b [1][2] = 5;
  b [2] = (int*) malloc (3*sizeof(int));
  b [2][0] = 15;
  b [2][1] = 1;
  b [2][2] = 4;
  vector<int>linha0_b (3);
  vector<int>linha1_b (3);
  vector<int>linha2_b (3);
  vector<vector<int>>matriz_b = {linha0_b, linha1_b, linha2_b};
  matriz_b=GetMatrix (3, 3, b, matriz_b);
  cout << "\nMatriz B" << endl;
  for(int i_b = 0 ; i_b < matriz_b.size(); i_b++)
    {
      for (int j_b = 0 ; j_b < matriz_b[i_b].size() ; j_b++)
	printf ("%2d ", matriz_b[i_b][j_b]);
      cout << endl;
    }

  
  int** c = (int**) malloc (3*sizeof(int*));
  c [0] = (int*) malloc (2*sizeof(int));
  c [0][0] = 5;
  c [0][1] = 1;
  c [1] = (int*) malloc (2*sizeof(int));
  c [1][0] = 10;
  c [1][1] = 2;
  c [2] = (int*) malloc (2*sizeof(int));
  c [2][0] = 15;
  c [2][1] = 1;
  vector<int>linha0_c (2);
  vector<int>linha1_c (2);
  vector<int>linha2_c (2);
  vector<vector<int>>matriz_c = {linha0_c, linha1_c, linha2_c};
  matriz_c=GetMatrix (3, 2, c, matriz_c);
  cout << "\nMatriz C" << endl;
  for(int i_c = 0 ; i_c < matriz_c.size(); i_c++)
    {
      for (int j_c = 0 ; j_c < matriz_c[i_c].size() ; j_c++)
	printf ("%2d ", matriz_c[i_c][j_c]);
      cout << endl;
    }

  map< string,  vector<vector<int>>> Mmap;
  Mmap ["A"] = matriz_a;
  Mmap ["B"] = matriz_b;
  Mmap ["C"] = matriz_c;

  char pedido [1];
  int teste_pedido;
  printf ("\nDigite a letra (A, B ou C) da matriz que deseja que seja mostrada: ");
  teste_pedido = scanf ("%c", pedido);
  if ( (teste_pedido != 1) || ((pedido[0] != 'A') && (pedido[0] != 'B') && (pedido[0] != 'C')) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }
  string s = pedido;
  cout << "\nMatriz retornada:" << endl;

  vector<int>linha0 (3);
  vector<int>linha1 (3);
  vector<int>linha2 (3);
  vector<vector<int>>matriz = {linha0, linha1, linha2};

  matriz = Mmapfind (s, Mmap);

  for(int i = 0 ; i < matriz.size(); i++)
    {
      for (int j = 0 ; j < matriz[i].size() ; j++)
	{
	  if (matriz[i][j] == 0)
	    break;
	  printf ("%2d ", matriz[i][j]);
	}
      cout << endl;
    }

  free (a[0]);
  free (a[1]);
  free (a);
  linha0_a.clear ();
  linha1_a.clear ();
  matriz_a.clear ();
  free (b[0]);
  free (b[1]);
  free (b[2]);
  free (b);
  linha0_b.clear ();
  linha1_b.clear ();
  linha2_b.clear ();
  matriz_b.clear ();
  free (c[0]);
  free (c[1]);
  free (c[2]);
  free (c);
  linha0_c.clear ();
  linha1_c.clear ();
  linha2_c.clear ();
  matriz_c.clear ();
  Mmap.clear ();
  linha0.clear ();
  linha1.clear ();
  linha2.clear ();
  matriz.clear ();

  cout << "\n -FIM-\n" << endl;
  return 0;
}
