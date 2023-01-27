/* **************************************************************************
*                                                                           *
*              Série 4 (04/11/2019), exercício 4 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// Função a aplicar quando é digitado algo inválido no terminal

void help ()
{
  printf ("\nERRO: Deve digitar './[nome do programa] [String 1] [String 2]'.\n");
  printf ("\n");
  exit (1);
}


// Função que retorna o comprimento da string

int str_len (const char *str)
{
  int i = 0;   // Contador

  while (str [i] != 0)
      i += 1;

  // Como i começa com i = 0, tem-se que, no final do ciclo, i dará o número total de caracteres da string
  
  return i;
}


// Função que copia uma string para outra string

char *str_cpy (char *str1, const char *str2)
{
  int i = 0; // Contador

  while (str2 [i] != 0)
    {
      str1 [i] = str2 [i];
      i += 1;
    }

  str1 [i] = 0;  // Dar o terminador à posição final da nova string

  return str1;   // Retornar ponteiro para nova string
}


// Primeira função que junta duas strings

char *str_cat1 (char *str1, const char *str2)
{
  int i1 = 0;   // Contador para comprimento de str1

  int i2 = 0;   // Contador para junção de str2 a str1

  while (str1 [i1] != 0)
    i1 += 1;

  // Como i1 inicia-se em 0, i1 final é o comprimento de str1
  
  while (str2 [i2] != 0)
    {
      str1 [i1 + i2] = str2 [i2];
      i2 += 1;
    }

  // Foram acrescentados a str1 os elementos de str2
  
  str1 [i1 + i2] = 0;  // Atribuir o valor zero (terminador) à posição final da junção das strings
  
  return str1;         // Retornar ponteiro para a junção das strings
}


//  Segunda função para juntar duas strings (alínea d)

char *str_cat2 (char *str1, const char *str2)
{
  int l;

  l = str_len (str1);               // Calcular o comprimento de str1, recorrendo a uma função já definida

  str_cpy (&str1 [l], str2);        // Adicionar str2 a str1, usando uma função já definida

  str1 [l + str_len (str2)] = 0;    // Atribuir o terminador à posição final

  return str1;                      // Retornar ponteiro para nova string
}



int main (int argc, char **argv)
{
  // Declaração das variáveis

  int  l1, l2;  // Comprimento das strings 1 e 2, respetivamente
  char *s;      // String para onde é copiada a 1ª string e juntada a 2ª string

  // Teste da leitura

  if (argc != 3)
    help ();

  // Título do programa
;
  printf  ("\n *-*-*-*-* Strings *-*-*-*-*\n");

  // Retornar comprimentos das strings utilizando a função str_len construída (alínea a)

  printf ("\n -Comprimento das strings digitadas:\n");

  l1 = str_len (argv [1]);
  printf ("\nA string '%s' tem %d caracteres.", argv [1], l1);

  l2 = str_len (argv [2]);
  printf ("\nA string '%s' tem %d caracteres.\n", argv [2], l2);

  
  // Alocação de memória para a string s (número de caracteres total, mais a posição para o terminador)

  s = (char*) malloc ((l1 + l2 + 1) * sizeof (char));

  // Copiar o primeiro argumento para outra string, usando a função str_copy construída (alínea b)

  str_cpy (s, argv [1]);
  printf ("\n -A primeira string, '%s', foi copiada para outra string. O resultado é '%s'.\n", argv [1], s);

  
  // Juntar a segunda string à nova string, usando a função str_cat1 construída (alínea c)

  str_cat1 (s, argv [2]);
  printf ("\n -Concatenação das strings 1 e 2, digitadas no terminal: '%s'.\n", s);

  
  // Testar a nova função, str_cat2
  
  str_cpy (s, argv [1]);  // Copiar, de novo, a primeira string
  str_cat2 (s, argv[2]);  // Adicionar a segunda string digitada
  
  printf ("\n -Concatenação das strings 1 e 2 recorrendo a outra função: '%s'.\n", s);

  
  // Terminar o programa

  free (s);  // Libertar a memória da string s

  printf ("\n *FIM*\n");
  printf ("\n");

  return 0;
}
