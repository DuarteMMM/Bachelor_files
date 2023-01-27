/* ***************************************************************************
 *                                                                           *
 *              Série 6 (18/11/2019), exercício 3 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void mostrar_no_ecra (unsigned short int* p)
{
  int i = 0;  // Contador

  printf ("\nSequência: \n");
  while (i < 16)
    {
      printf ("%hu", p [i]); // Escrever no ecrã
      i += 1; // Incrementar o contador
    }
  printf ("\n");
}

int main ()
{
  unsigned short int p [16]  ; // Vetor de zeros e uns
  int                i = 0   ; // Contador para obter os zeros e uns
  int                posicao ; // Posição do spin a mudar
  int                teste1  ; // Teste da leitura da posição
  int                escolha ; // Para continuar ou parar o ciclo
  int                teste2  ; // Teste da leitura da escolha

  printf ("\n        *-*-*-*-* Rede de spins *-*-*-*-*\n");
  printf ("(o zero representa o spin -1/2 e o um representa o spin 1/2)\n");

  srand (time (NULL));

  // Gerar zeros e uns		     

  while (i < 16)
    {
      p [i] = (rand ()) % 2; // Restos das divisões serão zero ou um
      i += 1; // Incremento
    }
  
  mostrar_no_ecra (p); // Mostrar no ecrã a sequência de zeros e uns

  // Perguntar qual o spin a trocar

  printf ("\nQual a posição (1 a 16) cujo spin deseja alterar?\n");
  teste1 = scanf ("%d", &posicao);  // Leitura

  // Teste de leitura

  if ( (teste1 != 1) || (posicao < 1) || (posicao > 16) )
    {
      printf ("\nDigitou um valor inválido.\n");
      printf ("\n-FIM-\n");
      return 1;
    }

  // Trocar o spin

  unsigned short int a ; // Anterior valor (isto é necessário, porque se atribuísse zero a um valor que era um, depois no if seguinte, o valor era 1 e atribuia zero outra vez

  a = p [posicao - 1];
  
  if (a == 0)
    p [posicao - 1] = 1;

  if (a == 1)
    p [posicao - 1] = 0;

  printf ("\n-Nova sequência-\n");
  mostrar_no_ecra (p); // Mostrar no ecrã a nova sequência

  // Ciclo

  while (1)
    {

      printf ("\nDeseja mudar o spin de outra posição?\n(1)Sim;\n(2)Não.\n");
      teste2 = scanf ("%d", &escolha);

      if ((teste2 != 1) || (escolha > 2) || (escolha < 1))
	{
	  printf ("\nERRO: Deve digitar 1 ou 2.\n");
	  break;
	}

      if (escolha == 2)
	break;

      // Perguntar qual o spin a trocar

      printf ("\nQual a posição (1 a 16) cujo spin deseja alterar?\n");
      teste1 = scanf ("%d", &posicao);  // Leitura

      // Teste de leitura

      if ( (teste1 != 1) || (posicao < 1) || (posicao > 16) )
	{
	  printf ("\nDigitou um valor inválido.\n");
	  printf ("\n-FIM-\n\n");
	  return 1;
	}

      // Trocar o spina

      a = p [posicao - 1];

      if (a == 0)
	p [posicao - 1] = 1;

      if (a == 1)
	p [posicao - 1] = 0;

      printf ("\n-Nova sequência-\n");
      mostrar_no_ecra (p); // Mostrar no ecrã a nova sequência
    }

  printf ("\n-FIM-\n\n");
  return 0;
}
