/* ***************************************************************************
 *                                                                           *
 *              Série 7 (25/11/2019), exercício 3 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char **argv)
{
  int  n             ; // Valor máximo
  int  teste1        ; // Teste da leitura do valor máximo
  int  *v            ; // Vetor
  int  i = 2         ; // Contador para "percorrer" o vetor até sqrt (n)
  int  j = 2         ; // Contador para "percorrer" o vetor para cada i
  int  Teste         ; // Raiz quadrada de n
  int  soma = 1      ; // Números primos escritos no terminal até ao momento (usado para escrever em 6 colunas) 
  FILE *f            ; // Ficheiro
  char s_n           ; // Sim ou não (resposta do utilizador acerca da leitura do ficheiro)
  int  ordem         ; // Ordem do número primo
  int  teste2        ; // Teste para a leitura da ordem do número primo
  int  nr_primos = 0 ; // Quantidade de números primos
  int  nr_ciclos = 0 ; // Número de ciclos de leituras do ficheiro

  printf ("\n *-*-*-*-* Números primos até um certo valor máximo *-*-*-*-*\n"); // Título

  // Leitura do valor máximo do terminal e testar o que foi digitado no mesmo

  if (argc != 2)
    {
      printf ("\nERRO: Deve digitar: './[nome do programa] [valor máximo]'\n\n");
      return 1;
    }
  
  teste1 = sscanf (argv [1], "%d", &n);

  if ((teste1 != 1) || (n <= 1))
    {
      printf ("\nERRO: Deve digitar um número natural maior que 1. Se digitar um valor real, é considerada a respetiva parte inteira.\n\n");
      return 2;
    }

  v = (int*) calloc (n+1, sizeof (int)); // Alocação do vetor, colocando-se todos os seus valores em "0"

  Teste = sqrt (n); // Calcular a raiz quadrada de n (por defeito, pois "Teste" é um inteiro)

  // O zero e o um não são números primos, logo atribui-se o valor "1" (embora o 0 e o 1 não sejam considerados nos ciclos posteriores)

  v [0] = 1;
  v [1] = 1;
  
  // Começando em i=2, e até i=Teste, coloca-se o valor "1" nos valores múltiplos de i (logo, números não primos)

  while (i <= Teste)
    {
      j = i + 1; // O primeiro número a seguir a i, onde se começará o ciclo de comparações

      // Não se comparará com os números seguintes se se já souber que i não é primo (tem "1"); só se compara se ainda tiver "0" no vetor
       
      if (v [i] == 0)
	{
	  while (j <= n)
	    {
	      // Verificar se os números a seguir ao i são múltiplos
      
	      if ((j % i) == 0)
		{
		  v [j] = 1; // Se for múltiplo, colocar "1" no vetor
		}
	      
	      j += 1; // Avança 1 no j
	    }
	}
      
      i += 1;  // Avança 1 no i
    }

  // No final deste ciclo, os números primos possuem o valor "0" (do calloc realizado) e os não primos possuem o valor "1"
  
  i = 2 ; // Colocar de novo o valor 2 em i para a escrita dos primos no terminal e no ficheiro

  // Abertura do ficheiro em binário e respetivo teste

  f = fopen ("Números primos", "wb+");

  if (f == NULL)
    {
      printf ("\nERRO: O ficheiro não abriu corretamente.\n\n");
      return 3;
    }

  printf ("\nNúmeros primos até %d (inclusive):\n", n);

  // Escrever os números primos no terminal (em 6 colunas) e no ficheiro
    
  while (i <= n)
    {
      if (v [i] == 0)
	{
	  if (((soma-1) % 6) == 0)
	    printf ("\n");  // Mudar de linha no terminal, se necessário
	  printf ("%-5d   ", i);  // Escrever no terminal
	  
	  fwrite(&i, sizeof (unsigned int), 1, f);  // Escrever no ficheiro em binário

	  soma += 1; // Incremento, de modo a saber se será necessária mudança de linha
	  nr_primos += 1; // Acrescentar 1 ao total de números primos
	}
      
      i += 1;
    }

  printf ("\n\nExistem %d números primos até %d.\n", nr_primos, n);

  // Ciclo de leituras de números do ficheiro e respetiva escrita no terminal
  
  while (1)
    {
      if (nr_ciclos == 0)
	{
	  printf ("\n-Deseja ler algum número do ficheiro? S [sim] ou N [não] ?\n  ");
	  nr_ciclos += 1;
	}
      
      else
	printf ("\n\n-Deseja ler outro número do ficheiro? S [sim] ou N [não] ?\n  ");
      
      scanf (" %c", &s_n); // Adicionou-se o espaço em branco antes de %c para que o programa funcionasse devidamente

      // Testar a resposta que foi digitada

      if ((s_n == 78) || (s_n == 110))
	break;

      if ((s_n != 78) && (s_n && 110) && (s_n != 83) && (s_n != 115))
	{
	  printf ("\nDigitou algo inválido. Deve escrever 'S' ou 's' (para 'Sim') ou 'N' ou 'n' (para 'Não').\n");
	  printf ("O programa também terminará se tiver digitado um número real não inteiro para a ordem do número primo.\n");
	  break;
	}

      // Leitura e teste da leitura da ordem do número primo

      printf ("Qual a ordem do número primo que deseja saber? (o número 2 tem ordem 1)\n  ");
      teste2 = scanf ("%d", &ordem);

      if ((teste2 == 0) || (ordem < 1) || (ordem > nr_primos))
	{
	  printf ("\nDigitou um valor inválido.\nSelecione um número natural até %d, inclusive (total de números primos).\n", nr_primos);
	  printf ("O programa também terminará se tiver digitado mais do que um caracter na pergunta de 'Sim'/'Não'.\n");
	  break;
	}

      fseek(f, (ordem-1)*sizeof (int), SEEK_SET); // Posicionar no ficheiro
 
      fread(&i, sizeof (int), 1, f);  // Ler do ficheiro

      printf ("O número primo de ordem %d é: %d\n", ordem, i);  // Escrever no terminal
    }

  // Finalizar o programa
  
  printf ("\n-FIM-\n\n");
  fclose (f); // Fechar o ficheiro
  free (v); // Libertar a memória de v
  return 0;
}
  
      
          
  
  
