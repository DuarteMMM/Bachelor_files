/******************************************************
 *                Física Computacional                *
 *                    Exercício 19                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <iostream>
#include <cstdio>
using namespace std;

void Mmultiply (double **mx, double *vr, int n, int m, double *pt)
{
  int contador_linhas=0, contador_colunas=0;

  while (contador_linhas < m)
    {
      while (contador_colunas < n)
	{
	  pt [contador_linhas]+=mx[contador_linhas][contador_colunas]*vr[contador_colunas];
	  contador_colunas++;
	}
      contador_linhas++;
    }
}

int main ()
{
  printf ("\n-=-=-=- Exercício 19 -=-=-=-");

  int colunas, teste_colunas, linhas, teste_linhas;
  
  printf ("\n\nQuantas colunas deseja que a matriz mx tenha? (o vetor terá o mesmo número de linhas) ");
  teste_colunas = scanf ("%d", &colunas);
  if ( (teste_colunas != 1) || (colunas < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 1;
    }
  
  printf ("\nQuantas linhas deseja que a matriz mx tenha? ");
  teste_linhas = scanf("%d", &linhas);
  if ( (teste_linhas != 1) || (linhas < 1) )
    {
      printf ("\nDigitou algo inválido.\n\n");
      return 2;
    }
  
  double **mx = (double**) malloc (linhas*sizeof (double*));
  
  int contador_linhas = 0, contador_colunas = 0, teste_valores_mx;
  printf ("\n");
  while (contador_linhas < linhas)
    {
      mx [contador_linhas] = (double*) malloc (colunas*sizeof (double));
 
      while (contador_colunas < colunas)
	{
	  if (contador_colunas==0)
	    printf ("Digite um valor double para a linha %d: ", contador_linhas+1);
	  if (contador_colunas>0)
	    printf ("Digite outro valor double para a linha %d: ", contador_linhas+1);
	  teste_valores_mx = scanf ("%lf", &mx[contador_linhas][contador_colunas]);
      
	  if (teste_valores_mx != 1)
	    {
	      printf ("\nDigitou algo inválido.\n\n");
	      return 3;
	    }

	  contador_colunas++;
	}
      printf ("\n");
      contador_colunas = 0;
      contador_linhas++;
    }

  printf ("-=-=-=-=-=-\n\n");
  
  double *v = (double*) malloc (colunas*sizeof (double));

  int teste_valores_v;

  while (contador_colunas < colunas)
    {
      printf ("Digite o valor double para a linha %d do vetor: ", contador_colunas+1);
      teste_valores_v = scanf ("%lf", &v[contador_colunas]);

      if (teste_valores_v != 1)
	{
	  printf ("\nDigitou algo inválido.\n\n");
	  return 4;
	}

      contador_colunas++;
    }

  contador_linhas=0;

  printf ("\n -=-=-=-=-=-\n");
  
  double *produto = (double*) calloc (linhas, sizeof(double));
  Mmultiply (mx, v, colunas, linhas, produto);
  
  printf ("\nAs entradas do vetor resultante do produto são, aproximadamente:");
  while (contador_linhas < linhas)
    {
      printf ("   %.1lf", produto[contador_linhas]);
      contador_linhas++;
    }

  contador_linhas=0;
  
  // Libertar memória

  while (contador_linhas < linhas)
    {
      delete mx[contador_linhas];
      contador_linhas++;
    }
  delete [] mx;
  delete [] v;
  
  printf ("\n\n -FIM-\n\n");
  
  return 0;
}

// Com este programa, consegue-se fazer o produto mencionado na alínea c do exercício anterior, escolhendo v=(2, 5, 7).
  
