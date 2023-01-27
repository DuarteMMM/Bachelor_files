/* **************************************************************************
 *                                                                           *
 *              Série 5 (11/11/2019), exercício 2 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>

// Função que ordena os valores a apresentar (bubblesort)

void ordenar (double *v, int x)
{
  int    n, i ;
  double z    ;
    
  while (1)
    {
      n = 0;
      for (i = 0; i < x-1; ++i)
        {
	  if (v [i] > v [i+1])
	    {
	      z = v [i];
	      v [i] = v [i + 1];
	      v [i + 1] = z;
	      n = 1;
	    }
        }
        
      if (n == 0)
	break;
    }
}

// Função que elimina os valores repetidos

int eliminar (double *v, int x)
{
  int n = 0, i; // Contadores

  /* Vão-se comparando os valores do vetor; se, por exeplo, v [0]=v [1]= ... igual até v [5], só quando se chega ao v [6] se faz v [n=0]=v[5], ou seja, o novo vetor v só ficar com esse valor uma vez (no n=0) */
  
  for (i = 0; i < x-1; i++)
    {
      if (v [i] != v [i + 1])
        {
	  v [n] = v [i + 1];
	  n++;
        }
    }
    
  v = (double*) realloc (v, n * sizeof (double)); // Reajuste do tamanho do vetor para o novo tamanho //
    
  return n;
}


int main (int argc, char **argv)
{
  // Declaração de variáveis

  int     n1, n2       ;      // Testes de leituras
  char    *ptr1, *ptr2 ;      // Para testes de leituras
  int     n, m         ;      // Limites superiores dos intervalos de naturais

  int     z, i         ;      // Contadores para ciclos
  int     x = 0        ;      // Contador para guardar valores no vetor
    
  int     b            ;      // Número de elementos do novo vetor
  double  *v           ;      // Vetor dos números racionais
    
  FILE    *f1          ;   // Declaração do ficheiro
    
  x=0;
    
  // Testes de leitura

  if (argc != 3)
    {
      printf ("\nERRO: Insira dois números naturais, N e M, separados por um espaço em branco, com N <= M.\n");
      printf ("\n");
      return 1;
    }

  n1 = strtol (argv [1], &ptr1, 10);
  n2 = strtol (argv [2], &ptr2, 10);

  if (((*ptr1) != 0) || ((*ptr2) != 0) || (argv [1] <= 0) || (argv [2] <= 0) || (argv [1] > argv [2]))
    {
      printf ("\nERRO: Insira dois números naturais, N e M, separados por um espaço em branco, com N<=M.\n");
      printf ("\n");
      return 2;
    }
    
  // Leitura dos valores de N e de M da linha de comandos
    
  sscanf (argv [1], "%d", &n);
  sscanf (argv [2], "%d", &m);

  // Abertura do ficheiro e respetivo teste
  
  f1 = fopen ("dados.txt", "wt");
  if (f1 == NULL)
    {
      printf ("\nERRO: Não foi possível abrir o ficheiro.\n");
      printf ("\n");
      return 3;
    }
    
  v = (double*) malloc (m * n * (sizeof (double))); // Alocação do espaço mínimo necessário
    
  // Cálculo dos racionais pelo quociente de N e M e guardar no vetor
    
  for (z = 1; z <= n; z++)
    {
      for (i = 1; i <= m; i++)
        {
	  v [x] = (double) z / (double) i;
	  x += 1;
        }
    }
    
  // Ordenação dos valores e eliminação dos repetidos
    
  ordenar (v, m*n);
  
  b = eliminar (v, m*n);   // Este "b" é o novo número de elementos do vetor
    
  // Impressão dos valores no ficheiro e no ecrã

  printf ("\n *-*-*-*-* Números racionais *-*-*-*-*\n");
  fprintf (f1, "*-*-*-*-* Números racionais *-*-*-*-*\n");
    
  for (z = 0; z < b; z++)
    {
      fprintf (f1, "\n%lf", v [z]);
      printf ("\n%lf", v[z]);
    }

  // Terminar o programa

  printf ("\n");
  fprintf (f1, "\n");
  printf ("\n -FIM-\n");
  fprintf (f1, "\n -FIM-");
  printf ("\n");
  fclose (f1); // Encerramento do ficheiro
  free (v);    // Libertação do espaço de memória
    
  return 0;
}
