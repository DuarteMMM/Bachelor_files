/* ***************************************************************************
 *                                                                           *
 *              Série 7 (25/11/2019), exercício 2 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Estrutura

typedef struct
{
  double Re  ;
  double Im  ;
  double Mod ;
} Complexo;


// Módulo de um Complexo

void C_Mod (Complexo *z)
{
  z->Mod = (z->Re * z->Re) + (z->Im * z->Im);
  z->Mod = sqrt (z->Mod);
}


// Trocar os Ponteiros para Dois Complexos

void C_Trade (Complexo **z, Complexo **w)
{
  Complexo *l ;

  l = *z;
  *z = *w;
  *w = l;
}


// QuickSort de Complexos

void C_QuickSort (Complexo **v, int esq, int dir)
{
  int     i   = esq             ;
  int     j   = dir             ;
  int     m   = (esq + dir) / 2 ;
  double  piv = v [m]->Mod       ;

  while (i <= j)
    {
      while (v [i]->Mod > piv)
	i++;
      
      while (piv > v [j]->Mod)
	j--;
      
      if (i <= j)
	{
          C_Trade (&v[i], &v[j]);
          i++;
	  j--;
	}
    }
  
  if (esq < j)
    C_QuickSort (v, esq, j);
  
  if (i < dir)
    C_QuickSort (v, i, dir);
}


// Print de complexos

void C_Print (Complexo *z, int i)
{
  if (z->Re>0)
    printf ("    z(%2d)  =    %6.3lf ", i+1, z->Re);

  else if (z->Re<0)
    printf ("    z(%2d)  =  - %6.3lf ", i+1, -z->Re);
    
  if (z->Im>0)
    printf ("+ %6.3lf i", z->Im);

  else if (z->Im<0)
    printf ("- %6.3lf i", -z->Im);

  printf ("     ;     |z(%2d)|  =  %7.3lf\n", i+1, z->Mod);
}


// Main

int main (int argc, char **argv)
{
  // Declaração das Variáveis
  
  int        N = 0 ;  // Total de números complexos a gerar
  int        teste1;  // Teste da leitura de N
  Complexo   **v   ;  // Vetor de complexos
  int        i = 0 ;  // Contador de ciclos
  int        j = 1 ;  // Contador de ciclos
  int        p = 0 ;  // Posição do primeiro complexo a trocar
  int        q = 0 ;  // Posição do segundo complexo a trocar

  // Leitura do valor do terminal e respetivo teste
  
  printf ("\n *-*-*-*-* N números complexos aleatórios de partes em [-8, 16] *-*-*-*-*\n");  // Título

  if (argc != 2)
    {
      printf ("\nERRO: Deve digitar: './[nome do programa] [valor de N]'\n\n");
      return 1;
    }

  teste1 = sscanf (argv [1], "%d", &N);

  if ((teste1 == 0) || (N < 2))
    {
      printf ("\nERRO: N deve ser um número natural maior que 1 (se digitar um real, será considerada a respetiva parte inteira.\n\n");
      return 2;
    }
  
  // Alocar espaço para o vetor de complexos
  
  v = (Complexo**) malloc (N * sizeof (Complexo*) );

  for (i = 0; i < N; i++)
    v [i] = (Complexo*) malloc (N * sizeof (Complexo) );

  // Gerar complexos e calcular o seu módulo
  
  srand (time (NULL));

  for (i = 0; i < N; i++)
    {
      v [i]->Re = ((double) rand () / (double) RAND_MAX) * 24 - 8;
      v [i]->Im = ((double) rand () / (double) RAND_MAX) * 24 - 8;

      C_Mod (v [i]);
    }


  // Alínea a): ordenar os complexos por ordem decrescente das suas normas e escrevê-los no ecrã (incluindo a sua norma)

  printf ("\nOs números complexos gerados, por ordem decrescente das normas, são os seguintes:\n");
  C_QuickSort (v, 0, N - 1);

  for (i = 0; i < N; i++)
    C_Print (v [i], i);
    
  // Alínea b): perguntar ao utilizador se deseja trocar a ordem de algum par de complexos e, no caso afirmativo, executar a troca, mostrá-los novamente no ecrã e voltar a fazer a pergunta
  
  printf("\nDeseja trocar a posição de algum par de complexos?\nSe sim, digite '[ordem] [ordem]' (ordens (válidas) dos números).\n");
  
  while (1)
    {
      if ((scanf("%d %d", &p, &q) != 2) || (p < 2) || (q < 2) || (p > N) || (q > N) || (p == q))
	break;

      printf ("\nResultado da troca do complexo na posição %d com o complexo na posição %d:\n", p, q);

      C_Trade (&v[p-1], &v[q-1]);

      for (i = 0; i<N; i++)
	C_Print (v[i], i);
      
      j++;
      
      printf ("\nDeseja trocar a posição de outro par de complexos?\nSe sim, digite, de novo, [ordem] [ordem].\n");
    }

  // Libertar o espaço alocado
  
  for (i = 0; i < N; i++)
    free (v [i]);
  
  free (v);

  // Finalizar o programa
  
  printf ("\n-FIM-\n\n");
  return 0;
}

