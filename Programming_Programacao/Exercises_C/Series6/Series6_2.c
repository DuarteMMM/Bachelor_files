/* **************************************************************************
*                                                                           *
*              Série 6 (18/11/2019), exercício 2 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função a executar no caso de digitações incorretas no terminal

void help ()
{
  printf ("\n *-*-*-*-* Escrita num ficheiro na ordem inversa *-*-*-*-*\n");
  printf ("\nERRO: Digitou algo inválido. Deve escrever:\n");
  printf ("\n ./[nome do programa] [nome do ficheiro 1] [nome do ficheiro 2]\n");
  printf ("\n Notas: o ficheiro 1 deve ser criado previamente por si. Não é aconselhável colocar caracteres acentuados\n");

  printf ("\n");

  exit (1);
}

int main (int argc, char** argv)
{
  FILE    *f1 ,*f2  ;   // Ficheiros de leitura e escrita, respetivamente
  int     i = 0     ;   // Contador para preenchimento do vetor v
  int     j = 0     ;   // Para utilizar em 'fgetc'
  char    *v        ;   // Vetor para caracteres do ficheiro

  // Teste da quantidade de valores digitados no terminal

  if (argc != 3) 
    help ();
    
  // Abertura e teste de abertura do ficheiro 1 (ficheiro de leitura)

  f1 = fopen (argv [1], "rt");

  if (f1 == NULL)
    {
      printf("\nERRO: O ficheiro '%s' não foi encontrado ou não abriu corretamente.\n", argv [1]);
      printf ("\n");
      return 1;
    }

  // Abertura e teste de abertura do ficheiro 2 (ficheiro de escrita)

  f2 = fopen (argv [2],"wt");

  if (f2 == NULL)
    {
      printf("\nERRO: O ficheiro '%s' não abriu corretamente.\n", argv [2]);
      printf ("\n");
      fclose (f1);   // Fechar o ficheiro 1
      return 2;
    }

  v = (char*) malloc (1024 * sizeof (int));  // Alocação do vetor v (pedida no exercício)

  // Ler os vários caracteres no ficheiro até chegar ao fim do mesmo (EOF)
  
  while ((j = fgetc (f1)) != EOF)
    {
      v [i] = j;  // Guardar o caracter no vetor v

      // No caso de se chegar a '\n', terminou a linha
      
      if (j == '\n')
	{
	  i = i - 1;  // Voltar atrás (para imediatamente antes de '\n')

	  // Escrever os caracteres no ficheiro 2, pela ordem inversa
	      
	  while (i >= 0)
	    {
	      fprintf (f2, "%c", v [i]);
	      i -= 1;
	    }
	  
	  fprintf (f2, "%c", '\n'); // Escrever, no final, a mudança de linha (depois do texto na ordem inversa)

	  i = -1; // Para que se faça i += 1, em seguida, e preencher o vetor v, de novo, a partir do zero
	}
      
      i += 1;  // Incrementar i para um novo ciclo (na mesma linha, caso não se tenha realizado o bloco if, ou numa nova linha)
    }

  // Nota: não se escreveu 'EOF'no final do ficheiro 2, pois tal "colocação" é feita automaticamente pelo sistema, ao fazer fclose (f2)

  // Finalizar o programa
  
  printf ("\nA escrita no ficheiro '%s' foi efetuada com sucesso.\n", argv [2]);
  printf ("\n");
  
  fclose (f1); // Fechar o ficheiro 1
  fclose (f2); // Fechar o ficheiro 2
  free (v);    // Limpar a memória do vetor v

  return 0;
}
