/******************************************************
 *                Física Computacional                *
 *                    Exercício 18                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream>
#include <cstdio>
using namespace std;

// Alínea a
double Trace (int** mx, int n)
{
  int i = 0;
  double traco = 0.;
  while (i<n)
    {
      traco += mx[i][i];
      i++;
    }
  return traco;
}

// Alínea b
int* Mrow(int i, int** mx, int m, int n)
{
  int contador=0;
  int* linhai=(int*) malloc (m*sizeof (int));
  while (contador < m)
    {
      linhai [contador] = mx [i][contador];
      contador++;
    }
  return linhai;
}

// Alínea c
int* ProductVector (int **mx, int *v, int linhas)
{
  int *resultado = (int*) calloc (linhas, sizeof(int));
  int contador_linhas=0;

  while (contador_linhas < linhas)
    {
      resultado [contador_linhas]+=mx[contador_linhas][0]*v[0]+mx[contador_linhas][1]*v[1]+mx[contador_linhas][2]*v[2];
      contador_linhas++;
    }

  return resultado;
}

// Alínea d
int** ProductMatrix (int **mx, int **my, int colunas, int linhas, int indice_comum)
{
  int contador_linhas=0, contador_colunas=0, contador_indice_comum=0;
  int **resultado = (int**) malloc (linhas*sizeof(int*));
  while (contador_linhas < linhas)
    {
      resultado [contador_linhas] = (int*) calloc (colunas, sizeof (int));
      contador_linhas++;
    }
  contador_linhas = 0;
  
  while (contador_linhas < linhas)
    {
      while (contador_colunas < colunas)
	{
	  while (contador_indice_comum < indice_comum)
	    {
	      resultado [contador_linhas][contador_colunas] += (mx [contador_linhas][contador_indice_comum]) * (my [contador_indice_comum][contador_colunas]);
	      contador_indice_comum++;
	    }
	  contador_indice_comum = 0;
	  contador_colunas++;
	}
      contador_indice_comum = 0;
      contador_colunas = 0;
      contador_linhas++;
    }
  
  return resultado;
}

int main ()
{
  printf ("\n-=-=-=- Exercício 18 -=-=-=-\n");
  
  // Alínea a
  double traco;
  int **m1 = (int**) malloc (2*sizeof (int*));
  m1 [0] = (int*) malloc (2*sizeof (int));
  m1 [1] = (int*) malloc (2*sizeof (int));
  m1 [0][0] = 2;
  m1 [0][1] = 10;
  m1 [1][0] = 5;
  m1 [1][1] = 7;
  traco = Trace (m1, 2);
  cout << "\nAlínea a: O traço da matriz dada é " << traco << ".\n" << endl;

  int contador_linha_m1;
  
  // Alínea b
  int **m2 = (int**) malloc (2*sizeof (int*));
  m2 [0] = (int*) malloc (3*sizeof (int));
  m2 [1] = (int*) malloc (3*sizeof (int));
  m2 [0][0] = 2;
  m2 [0][1] = 10;
  m2 [0][2] = 5;
  m2 [1][0] = 3;
  m2 [1][1] = 2;
  m2 [1][2] = 7;
  int i, j, teste_i;
  printf ("Alínea b:\nQue linha da matriz deseja saber (1 ou 2)? ");
  teste_i = scanf ("%d", &i);
  if ( (teste_i != 1) || (i <= 0 ) || (i >= 3) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }
  int *linhai;
  j = i-1;
  linhai = Mrow (j, m2, 3, 2);
  printf ("\nOs valores desssa linha são: %d  %d  %d.\n", linhai[0], linhai[1], linhai[2]);

  // Alínea c
  int *v = (int*) malloc (3*sizeof (int));
  v [0]=2;
  v [1]=5;
  v [2]=7;

  int numero, teste_numero;
  printf ("\nAlínea c:\nQuantas linhas deseja que a matriz M tenha? ");
  teste_numero=scanf("%d", &numero);
  if ( (teste_numero != 1) || (numero<1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 2;
    }
  int **m3 = (int**) malloc (numero*sizeof (int*));
  int contador_numero=0, teste_valores;
  while (contador_numero < numero)
    {
      m3[contador_numero] = (int*) malloc (3*sizeof (int));
      printf ("\nDigite os 3 valores inteiros para a linha %d, separados por um espaço em branco: ", contador_numero+1);
      teste_valores = scanf ("%d %d %d", &m3[contador_numero][0], &m3[contador_numero][1], &m3[contador_numero][2]);
      if (teste_valores != 3)
	{
	  printf ("\nDigitou algo inválido.\n\n");
	  return 3;
	}
      contador_numero++;
    }
  contador_numero=0;
  int *produto1 = (int*) malloc (numero*sizeof(int));
  produto1 = ProductVector (m3, v, numero);
  printf ("\nAs entradas do vetor resultante do produto são:");
  while (contador_numero < numero)
    {
      printf (" %d", produto1[contador_numero]);
      contador_numero++;
    }
  printf (".");
  
  // Alínea d
  int **m4 = (int**) malloc (3*sizeof (int*));
  m4 [0] = (int*) malloc (3*sizeof (int));
  m4 [1] = (int*) malloc (3*sizeof (int));
  m4 [2] = (int*) malloc (3*sizeof (int));
  m4 [0][0] = 5;
  m4 [0][1] = 1;
  m4 [0][2] = 3;
  m4 [1][0] = 10;
  m4 [1][1] = 1;
  m4 [1][2] = 5;
  m4 [2][0] = 15;
  m4 [2][1] = 1;
  m4 [2][2] = 4;

  int **m5 = (int**) malloc (2*sizeof (int*));
  m5 [0] = (int*) malloc (3*sizeof (int));
  m5 [1] = (int*) malloc (3*sizeof (int));

  m5 = ProductMatrix (m2, m4, 3, 2, 3);
  printf ("\n\nAlínea d: As entradas da matriz resultante do produto são:\n");

  int contador_colunas=0, contador_linhas=0;
  while (contador_linhas < 2)
    {
      while (contador_colunas < 3)
	{
	  printf (" %d", m5 [contador_linhas][contador_colunas]);
	  contador_colunas++;
	}
      contador_colunas=0;
      printf ("\n");
      contador_linhas++;
    }

  // Libertar memória

  delete m1[0];
  delete m1[1];
  delete [] m1;

  delete m2[0];
  delete m2[1];
  delete [] m2;

  contador_numero = 0;
  while (contador_numero < numero)
    {
      delete m3[contador_numero];
      contador_numero++;
    }
  delete [] m3;

  delete m4[0];
  delete m4[1];
  delete m4[2];
  delete [] m4;

  delete m5[0];
  delete m5[1];
  delete [] m5;

  delete [] v;

  delete [] linhai;

  delete [] produto1;
  
  printf ("\n -FIM-\n\n");
  
  return 0;
}
  
