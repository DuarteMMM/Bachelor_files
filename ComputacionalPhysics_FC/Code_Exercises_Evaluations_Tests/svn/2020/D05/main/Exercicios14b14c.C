/******************************************************
 *                Física Computacional                *
 *          Exercício 14, alíneas b e c (e d)         *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include "./Exercicios14b14c_fintv.h"
#include "./Exercicios14b14c_fdoublev.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Print vetores unidimensionais de inteiros
void print_int (int* v, int n_int) {
  int contador=0;
  while (contador < n_int)
    {
      printf ("%d ", v[contador]);
      contador++;
    }
}

// Print vetores bidimensionais de inteiros
void print_int (int** v, int colunas, int linhas) {
  int contador_colunas=0, contador_linhas=0;
  while (contador_linhas < linhas)
    {
      while (contador_colunas < colunas)
	{
	  printf ("%d ", v[contador_linhas][contador_colunas]);
	  contador_colunas++;
	}
      contador_linhas++;
      contador_colunas=0;
    }
}

// Print vetores tridimensionais de inteiros
void print_int (int ***v,int indice1, int indice2, int indice3) {
  int contador_indice1=0, contador_indice2=0, contador_indice3=0;
  while (contador_indice3 < indice3)
    {
      while (contador_indice2 < indice2)
	{
	  while (contador_indice1 < indice1)
	    {
	      printf ("%d ", v[contador_indice3] [contador_indice2] [contador_indice1]);
	      contador_indice1++;
	    }
	  contador_indice2++;
	  contador_indice1 = 0;
	}
      contador_indice3++;
      contador_indice2=0;
      contador_indice1=0;
    }
}

// Print vetores unidimensionais de doubles
void print_double (double* v, int n_double) {
  int contador=0;
  while (contador < n_double)
    {
      printf ("%.1lf ", v[contador]);
      contador++;
    }
}

// Print vetores bidimensionais de doubles
void print_double (double** v, int colunas, int linhas) {
  int contador_colunas=0, contador_linhas=0;
  while (contador_linhas < linhas)
    {
      while (contador_colunas < colunas)
	{
	  printf ("%.1lf ", v[contador_linhas][contador_colunas]);
	  contador_colunas++;
	}
      contador_linhas++;
      contador_colunas=0;
    }
}

// Print vetores tridimensionais de doubles
void print_double (double ***v,int indice1, int indice2, int indice3) {
  int contador_indice1=0, contador_indice2=0, contador_indice3=0;
  while (contador_indice3 < indice3)
    {
      while (contador_indice2 < indice2)
	{
	  while (contador_indice1 < indice1)
	    {
	      printf ("%.1lf ", v[contador_indice3] [contador_indice2] [contador_indice1]);
	      contador_indice1++;
	    }
	  contador_indice2++;
	  contador_indice1 = 0;
	}
      contador_indice3++;
      contador_indice2=0;
      contador_indice1=0;
    }
}

// Main
int main() {

  int coluna_a=0, linha_a=0, indice1_b=0, indice2_b=0, indice3_b=0, indice2_c=0, indice3_c=0;

  int **a = fintv (a, 100, 50);
  
  while (linha_a<50)
    {
      while (coluna_a<100)
	{
	  a[linha_a][coluna_a]={1};
	  coluna_a++;
	}
      linha_a++;
      coluna_a=0;
    }
  linha_a=0;

  /* Importante! Foi testada a função abaixo, e funciona como esperado, mas, para não encher o ecrã de valores, decidiu-se não fazer print dos valores.
     printf ("Valores da matriz a:\n");
     print_int (a, 100, 50);
  */

  printf ("O array bidmensional 'a' possui valores 1;\n");
  
  double ***b = fdoublev (b, 100, 50, 20);
  double ***c = fdoublev (c, 100, 50); // O índice 3, que é 20, fica implícito, devido ao protótipo da função double***fdoublev

  while (indice3_b < 20)
    {
      while (indice2_b < 50)
	{
	  while (indice1_b < 100)
	    {
	      b[indice3_b] [indice2_b] [indice1_b] = {5.};
	      c[indice3_b] [indice2_b] [indice1_b] = {5.};
	      indice1_b++;
	    }
	  indice2_b++;
	  indice1_b = 0;
	}
      indice3_b++;
      indice2_b=0;
      indice1_b=0;
    }

  indice3_b=0;

  /* Aqui aplicou-se o mesmo critério mencionado acima

     printf ("\n\nValores do array b:\n");
     print_double (b, 100, 50, 20);

     printf ("\n\nValores do array c:\n");
     print_double (c, 100, 50, 20);

     printf ("\n\n-FIM-\n\n");
  */
  
  printf ("Os arrays bidmensionais 'b' e 'c' possuem valores 5.0.\n");
  
  while (linha_a < 50)
    {
      delete a[linha_a];
      linha_a++;
    }

  delete [] a;

  while (indice3_b < 20)
    {
      while (indice2_b < 50)
	{
	  delete b[indice3_b][indice2_b];
	  indice2_b++;
	}
      delete b[indice3_b];
      indice2_b=0;
      indice3_b++;
    }

  delete [] b;

  while (indice3_c < 20)
    {
      while (indice2_c < 50)
	{
	  delete c[indice3_c][indice2_c];
	  indice2_c++;
	}
      delete c[indice3_c];
      indice2_c=0;
      indice3_c++;
    }

  delete [] c;
  
  return 0;
}
