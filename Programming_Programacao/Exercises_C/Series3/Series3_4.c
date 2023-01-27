/* **************************************************************************
*                                                                           *
*              Série 3 (28/10/2019), exercício 4 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// Função que organiza por ordem crescente os números aleatórios gerados

void bubble_sort (int *a, int n)
{
  // Declaração de variáveis
  
  int i1;  //Contador
  int t;
  int x;
  
  while (1)
    {
      t = 0;

      // Trocar a ordem dos elementos
      
      for (i1 = 0; i1 < n - 1; ++i1)
	{
	  if (a [i1] > a [i1 + 1])
	    {
	      x = a [i1];
	      a [i1] = a [i1 + 1];
	      a [i1 + 1] = x;
	      t = 1;
	    }
	}

      //Parar a execução da função quando os elementos estão ordenados
      
      if (t == 0)
	break;
    }
}


// Função que calcula o número de vezes que cada valor apareceu

int* ocorrencias (int *a, int n)
{
  int i1, i2, i3;      // Contadores
  int total;           // Número de ocorrências de cada elemento
  int x;               // Usado para desprezar os elementos do vetor 'a' iguais a um que lhe é anterior (já considerado)
  int *b;              // Vetor da quantidade de ocorrências dos elementos

  i1 = 0;
  b = (int*) malloc (n * sizeof (int));   // Disponibilizar a memória necessária ao vetor b
  
  while (i1 < n)
    {
      total = 0;
      i2 = 0;
      x = 0;
      i3 = 1;

      // Verificar se o elemento já foi visto anteriormente: se sim, dá-se x=1 e não se calculam as ocorrências

      while (i3 < i1)
	{
	  if (a [i1] == a [i1 - i3])
	    x = 1;
	  i3 += 1;
	}

      // Se o elemento não for igual a nenhum anterior (x=0), calcula-se o número de ocorrências
      
      if (x == 0)
	{
	  while (i2 < n)
	    {
	      if (a [i1] == a [i2])
		total += 1;
	      i2 += 1;
	    }
	}

      b [i1] = total;  // Registar no vetor b o número de ocorrências para esse elemento

      i1 += 1;

    }
  
  return b;
}

// Função que determina a quantidade de números positivos gerados

int positivos (int *a, int n)
{
  int i;       // Contador
  int total;   // Quantidade de números positivos

  i = 0;
  total = 0;

  while (i < n)
    {
      if (a [i] >= 0)
	total += 1;
      i += 1;
    }

  return total;
}

// Função que determina a quantidade de números pares gerados

int pares (int *a, int n)
{
  int i;       // Contador
  int total;   // Quantidade de números pares

  i = 0;
  total = 0;

  while (i < n)
    {
      if ((a [i] % 2) == 0)
	total += 1;
      i += 1;
    }

  return total;
}


int main (int argc, char **argv)
{
  int   n;                          // Quantidade de números aleatórios a gerar
  int   teste, n1;                  // Testes de leitura de n
  char  *p1;                        // Teste (para verificar se n é natural)
  int   i;                          // Contador
  int   *a;                         // Vetor dos números aleatórios
  int   *o;                         // Vetor das ocorrências
  int   n_positivos, n_negativos;   // Quantidade de números positivos e negativos gerados, respetivamente
  int   n_pares, n_impares;         // Quantidade de números pares e ímpares gerados, respetivamente
  FILE  *f1;                        // Ficheiro de escrita

  // Verificar quantos elementos foram digitados no terminal
  
  if (argc != 2)
    {
      printf ("\nERRO: Digite (apenas) a quantidade de números aleatórios que deseja gerar (número natural).\n");
      printf ("\n");
      return 1;
    }

  // Testar o valor digitado no terminal: terá de ser um número natural (por isso, sem floating point)
  
  n1 = strtol (argv [1], &p1, 10);

  if ((n <= 0) || ((*p1) != 0))
    {
      printf ("\nERRO: Digite (apenas) a quantidade de números aleatórios que deseja gerar (número natural).\n");
      printf ("\n");
      return 2;
    }

  // Abrir o ficheiro (de escrita) e testar a sua abertura
  
  f1 = fopen ("Valores obtidos", "wt");
  
  if (f1 == NULL)
    {
      printf ("\nERRO: O ficheiro não abriu corretamente.\n");
      printf ("\n");
      return 3;
    }

  // Alocar o espaço necessário para o vetor dos números aleatórios
  
  a = (int*) malloc (n * sizeof (int));

  // Gerar e mostrar os números inteiros aleatórios em [-20, 79]

  if (n > 1)
    printf ("\n *-*-*-*-* Gerar %d números aleatórios *-*-*-*-*\n", n);

  if (n == 1)
    printf ("\n *-*-*-*-* Gerar 1 número aleatório *-*-*-*-*\n");
  
  i = 0;
  
  srand (time (NULL));

  if (n > 1)
    printf ("\n Números aleatórios gerados:\n");
  if (n == 1)
    printf ("\n Número aleatório gerado:\n");

  printf ("\n");
  
  while (i < n)
    {
      a [i] = rand() % 100 - 20;   // [0, RAND_MAX]->[0, 99]->[-20, 79]
      printf ("%5d", a [i]);

      // Trocar de linha depois de imprimir 6 elementos
      
      if ( ( ( (i+1) % 6 ) == 0 ) && (i != 0) )
	{
	  printf ("\n");
	  printf ("\n");
	}

      // Colocar ';' entre dois valores da mesma linha

      else
	{
	  if ( ( ( ( (i+1) % 6) != 0) && ( i < (n-1) ) || (i == 0) ) && (n != 1) ) 
	    printf ("   ;");
	}
      
      i += 1;
    }

  // No caso de n não ser múltiplo de 6, fazer parágrafo

  if ((n % 6) != 0)
    printf ("\n");

  // Ordenar os elementos de a por ordem crescente, de forma a dispô-los na tabela dessa maneira
  
  bubble_sort (a, n);

  // Alocar a memória necesária para o vetor das ocorrências e executar a função correspondente

  o = (int*) malloc (n * sizeof (int));
  o = ocorrencias (a, n);

  // Dispor os valores e as respetivas frequências absolutas numa tabela
  
  i = 0;
 
  printf ("\n   Elemento          Frequência absoluta\n");
  
  while (i < n)
    {
      if (o [i] != 0)
	printf ("\n     %3d                    %3d\n", a [i], o [i]);
      
      i += 1;
    }

  // Apresentar o máximo e o mínimo do conjunto de valores, que já se encontra por ordem crescente

  printf ("\n O máximo deste conjunto de valores é %d .\n", a [n-1]);
  printf (" O mínimo deste conjunto de valores é %d .\n", a [0]);

  // Calcular e apresentar a quantidade de números positivos e negativos, respetivamente

  n_positivos = positivos (a, n);
  n_negativos = n - n_positivos;

  if (n_positivos != 1)
    printf ("\n Foram gerados %d números positivos ", n_positivos);
  if (n_positivos == 1)
    printf ("\n Foi gerado 1 número positivo ");

  if (n_negativos != 1)
    printf ("e %d números negativos.\n", n_negativos);
  if (n_negativos == 1)
    printf ("e 1 número negativo.\n");

  printf ("  (NOTA: considerou-se o zero como um número positivo)\n");

  // Determinar e apresentar a quantidade de valores pares e ímpares, respetivamente

  n_pares = pares (a, n);
  n_impares = n - n_pares;

  if (n_pares != 1)
    printf ("\n Foram gerados %d números pares ", n_pares);
  if (n_pares == 1)
    printf ("\n Foi gerado 1 número par ");

  if (n_impares != 1)
    printf ("e %d números impares.\n", n_impares);
  if (n_impares == 1)
    printf ("e 1 número impar.\n");

  printf ("\n");

  // Escrever os valores obtidos no ficheiro

  fprintf (f1, "Quantidade de números gerados: %d\n", n);                             // Quantidade total
  fprintf (f1, "\nValor máximo:  %d\n", a [n-1]);                                     // Máximo
  fprintf (f1, "Valor mínimo:  %d\n", a [0]);                                         // Mínimo
  fprintf (f1, "\nQuantidade de números positivos ou nulos:  %d\n", n_positivos);     // Quantidade de números não negativos
  fprintf (f1, "Quantidade de números negativos:           %d\n", n_negativos);       // Quantidade de números negativos
  fprintf (f1, "\nQuantidade de números pares:   %d\n", n_pares);                     // Quantidade de números pares
  fprintf (f1, "Quantidade de números ímpares: %d\n", n_impares);                     // Quantidade de números ímpares

  // Dispor os valores e as respetivas frequências absolutas numa tabela, dentro do ficheiro
  
  i = 0;
  fprintf (f1, "\n  Elemento          Frequência absoluta\n");
  while (i < n)
    {
      if (o [i] != 0)
	fprintf (f1, "\n    %3d                    %3d\n", a [i], o [i]);
      i += 1;
    }
  
  // Terminar o programa

  fclose (f1);
  printf ("\n -FIM-\n");
  printf ("\n");

  return 0;
}
