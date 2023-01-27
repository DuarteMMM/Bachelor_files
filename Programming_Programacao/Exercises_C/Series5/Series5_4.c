/* **************************************************************************
 *                                                                           *
 *              Série 5 (11/11/2019), exercício 4 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 ************************************************************************** */
# include <stdio.h>
# include <time.h>
# include <stdlib.h>

int main (int argc, char **argv)
{
  int  n, m         ;   // Valores N e M
  int  n1, n2       ;   // Para testes de leituras de N e M
  char *ptr1, *ptr2 ;   // Idem

  char    *v     ;   // Vetor de "char"
  int     i = 0  ;   // Contador para N
  double  a      ;   // Número aleatório gerado

  int    soma_a = 0    ;  // Quantidade de spins 1/2
  int    soma_b = 0    ;  // Quantidade de spins -1/2
  double magnetizacao  ;  // Magnetização numa sequência

  int    j = 0                  ;  // Contador para M
  double soma_magnetizacoes = 0 ;  // Soma das magnetizações
  double magnetizacao_media     ;  // Magnetização média

  // Para a alínea d:

  double *soma ; // Vetor que guarda somas dos spins de ordem i (por exemplo, o primeiro spin atribuído em cada configuração)
      
  // Testes de leitura

  if (argc != 3)
    {
      printf ("\nERRO: Insira os dois números naturais, N e M, separados por um espaço em branco.\n");
      printf ("\n");
      return 1;
    }

  n1 = strtol (argv [1], &ptr1, 10);
  n2 = strtol (argv [2], &ptr2, 10);

  if (((*ptr1) != 0) || ((*ptr2) != 0) || (argv [1] <= 0) || (argv [2] <= 0))
    {
      printf ("\nERRO: Insira dois números naturais, N e M, separados por um espaço em branco.\n");
      printf ("\n");
      return 2;
    }

  printf ("\n *-*-*-*-* Modelo de Ising *-*-*-*-*\n");
  
  // Leitura dos valores de N e de M da linha de comandos
    
  sscanf (argv [1], "%d", &n);
  sscanf (argv [2], "%d", &m);

  v = (char*) malloc ((n + 1) * (sizeof (char))) ; // Alocação do espaço mínimo necessário
  soma = (double*) malloc ((n + 1) * (sizeof (double))); // Alocação do espaço mínimo necessário (este tem inteiros, logo não precisa de terminador)

  int q = 0; // Contador para dar zero a todos os elementos de "soma"

  while (q < n)
    {
      soma [q] = 0;
      q += 1;
    }
  
  v [n] = 0; // Terminador

  srand (time (NULL));

  while (j < m)
    {
      // Fazer configuração para a M-ésima vez
      
      while (i < n)
	{ 
	  a = ((double)rand ()) / ((double)RAND_MAX);   // Gerar número real entre 0 e 1

	  // Se o número gerado estiver em [0, 1/2[, dá-se o caracter 'a' (spin 1/2)
      
	  if (a < 0.5)
	    {
	      v [i] = 'a';
	      soma_a += 1;
	      soma [i] += 0.5;
	    }

	  // Se o número gerado estiver em [1/2, 1], dá-se o caracter 'b' (spin -1/2)

	  if (a >= 0.5)
	    {
	      v [i] = 'b';
	      soma_b += 1;
	      soma [i] += (-0.5);
	    }
      
	  i += 1;
	}

      // Calcular a magnetização para esta M-ésima sequência
      
      magnetizacao = ((soma_a * 0.5) + (soma_b * (-0.5))) / n;

      // Fazer prints: se não tiver o sinal negativo, tenho de o ajustar no terminal (para ficar esteticamente melhor)

      if (magnetizacao >= 0)
	printf ("\nMagnetização na %dª configuração:     %f\n",  j + 1, magnetizacao);

      if (magnetizacao < 0)
	printf ("\nMagnetização na %dª configuração:    %f\n",  j + 1, magnetizacao);

      soma_magnetizacoes += magnetizacao;  // Somar esta magnetização ao total de todas elas

      // Para um novo ciclo
      
      i = 0;
      soma_a = 0;
      soma_b = 0;
      
      j += 1;
    }

  // Calcular a média das M magnetizações

  magnetizacao_media = soma_magnetizacoes / m;
  printf ("\nA magnetização média é de %f.\n", magnetizacao_media);

  // Alínea d

  q = 0; // Por este contador em zero outra vez
  double total_magnetizacoes_por_spin = 0. ;
  double magnetizacao_media_por_spin       ;

  while (q < n)
    {
      total_magnetizacoes_por_spin += soma [q] / m;  // Divide-se por m porque em cada soma [q] há m spins
      q += 1;
    }

  magnetizacao_media_por_spin = total_magnetizacoes_por_spin / n;
  printf ("\nMagnetização média por spin (alínea d): %f.\n", magnetizacao_media_por_spin);

  // Terminar o programa

  free (v);
  printf ("\n -FIM-\n");
  printf ("\n");

  return 0;
}

// Verifica-se que a magnetização média e a magnetização média por spin são iguais e vão aproximando-se de zero quando se aumentam os números das iterações. //

      
