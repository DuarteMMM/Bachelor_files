/* **************************************************************************
*                                                                           *
*              Série 5 (11/11/2019), exercício 3 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help ()
{
  printf ("\nERRO: Digitou algo inválido. Deve escrever segundo uma das seguintes opções:\n");
  
  printf ("\n(1) Copiar o texto do ficheiro 1 para o ficheiro 2, transformando tudo em minúsculas:\n");
  printf ("\n ./[nome do programa] M2m [nome do ficheiro 1] [nome do ficheiro 2]\n");

  printf ("\n(2) Copiar o texto do ficheiro 1 para o ficheiro 2, transformando tudo em maiúsculas:\n");
  printf ("\n ./[nome do programa] m2M [nome do ficheiro 1] [nome do ficheiro 2]\n");

  printf ("\n Notas: o ficheiro 1 deve ser criado previamente; não são considerados os acentos.\n");

  printf ("\n");

  exit (1);
}

int main (int argc, char** argv)
{
  int     maximo    ;   // Quantidade de caracteres máximo numa linha
  int     teste     ;   // Teste da leitura de "maximo"
  FILE    *f1 ,*f2  ;   // Ficheiros de leitura e escrita, respetivamente
  int     l         ;   // Comprimento do vetor de cada linha do ficheiro
  int     j = 0     ;   // Contador para ver os caracteres de uma linha do ficheiro
  char    *teste1   ;   // Para verificar se já se chegou ao fim do ficheiro


  // Testes de leituras no terminal

  if (argc != 4) 
    help ();

  if (argc == 4)
    {
      if (((strcmp (argv [1], "M2m")) != 0) && ((strcmp (argv [1], "m2M")) != 0))
	help ();
    }

    
  // Abertura e teste de abertura do ficheiro 1 (ficheiro de leitura)

  f1 = fopen (argv [2], "rt");

  if (f1 == NULL)
    {
      printf("\nERRO: O ficheiro '%s' não foi encontrado ou não abriu corretamente.\n", argv [2]);
      printf ("\n");
      return 1;
    }

  // Abertura e teste de abertura do ficheiro 2 (ficheiro de escrita)

  f2 = fopen (argv [3],"wt");

  if (f2 == NULL)
    {
      printf("\nERRO: O ficheiro '%s' não abriu corretamente.\n", argv [3]);
      printf ("\n");
      fclose (f1);     // Fechar o ficheiro 1
      fclose (f2);

      // Nota: fecha-se o ficheiro 2, embora tenha havido problemas a abri-lo, para garantir que não se sai com um ficheiro "semi-aberto"
     
      return 2;
    }

  // Título

  printf ("\n *-*-*-*-* LEITURA E ESCRITA EM FICHEIROS *-*-*-*-*\n");

  // Perguntar o valor máximo de caracteres numa linha do ficheiro de leitura; testar a leitura desse número

  printf ("\nDigite o número máximo de caracteres numa linha do ficheiro 1 (para garantir uma cópia correta):\n");
  printf ("(Nota: se digitar um real, será considerada a respetiva parte inteira.)\n");
  printf ("\n");
  teste = scanf ("%d", &maximo);

  if (teste != 1)
    {
      printf ("\nDigitou algo inválido. Deve apresentar um número não negativo.\n");
      printf ("\n");
      return 3;
    }

  char v [maximo + 1];   // Vetor para a função 'fgets'

  while (1)
    {
      // Copiar os elementos de uma linha de f1 para o vetor v
      
      teste1 = fgets (v, maximo + 1, f1);

      // Testar se se chegou ao final do ficheiro
      
      if (teste1 == NULL)
	break;
      
      l = strlen (v);   // Número de dígitos naquela linha

      // maiúsculas -> minúsculas
      
      if ((strcmp (argv [1], "M2m")) == 0)
	{
	  while (j < l)
	    {
	      // Se houver maiúscula, por em minúscula
	    
	      if ((v [j] > 64) && (v [j] < 91))
		v [j] = v [j] + 32;

	      j += 1;
	    }

	  j = 0;
	  
	  fprintf (f2,"%s",v);
	}

      // minúsculas -> maiúsculas
      
      if ((strcmp (argv [1], "m2M")) == 0)
	{
	  while (j < l)
	    {
	      // Se houver minúscula, por em maiúscula
	    
	      if ((v [j] > 96) && (v [j] < 193))
		v [j] = v [j] - 32;

	      j += 1;
	    }

	  j = 0;
	    
	  fprintf (f2,"%s",v);
	}	  
    }

  // Finalizar o programa

  // free (v) ???;
  printf ("\nA escrita no ficheiro 2 foi efetuada.\n");
  printf ("\n -FIM-\n");
  printf ("\n");
  fclose (f1);
  fclose (f2);
  
  return 0;
}
