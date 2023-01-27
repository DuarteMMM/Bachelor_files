/* **************************************************************************
*                                                                           *
*              Série 2 (21/10/2019), exercício 3 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
  //Declaração de variáveis//
  
  char *b, *c;          //Strings//
  int d1, d2, d4, d5;   //Comprimento das strings//
  int d3;               //Resultado da comparação entre os comprimentos//
  int teste, teste1;    //Testes de leituras das strings//

  //Teste da leitura das strings no terminal//

  if (argc != 3)
    {
      printf ("\nERRO: Deve digitar, depois de './[nome do programa compilado] ', '[string] [string]'.\n");
      printf ("\nFIM\n");
      printf ("\n");
      return 1;
    }

  printf ("\n*-*-*-*-* Concatenação e comparação de strings *-*-*-*-*\n");
    
  //Comprimento das strings//

  d1 = strlen (argv [1]);
  d2 = strlen (argv [2]);

  //Apresentar no terminal as strings digitadas e seus comprimentos//

  printf ("\nA primeira string digitada foi:  '%s'.\nA segunda string digitada foi:   '%s'.\n", argv[1], argv[2]);
  printf ("\nComprimento da primeira string:  %d\nComprimento da segunda string:   %d\n", d1, d2);

  printf ("\n-De acordo com a função 'strcmp':\n");

  //Concatenação dos vetores (primeiro com o segundo, nesta ordem)//

  b = (char*) malloc ((d1 + d2 + 1) * sizeof (char));
  strcpy (b, argv [1]);
  strcat (b, argv [2]);
  d4 = strlen (b);
  printf ("\nPrimeiro string e segundo string concatenados, nesta ordem: '%s'\nComprimento: %d\n", b, d4);

  //Concatenção dos vetores (segundo com o primeiro, nesta ordem)//

  c = (char*) malloc ((d1 + d2 + 1) * sizeof (char));
  strcpy (c, argv [2]);
  strcat (c, argv [1]);
  d5 = strlen (c);
  printf ("\nSegundo string e primeiro string concatenados, nesta ordem: '%s'\nComprimento: %d\n", c, d5);

  //Comparação das duas strings criadas//

  d3 = strcmp (b, c);

  printf("\n-Comparação das strings criadas:");

  if (d3 > 0)
    printf ("\nA primeira é maior, segundo os critérios utilizados pela função 'strcmp'.\n");

  if (d3 < 0)
    printf ("\nA segunda é maior, segundo os critérios utilizados pela função 'strcmp'.\n");

  if (d3 == 0)
    printf ("\nAs strings são iguais, segundo os critérios da função 'strcmp'.\n");

  //Finalizar programa//

  free (b);
  free (c);

  printf ("\nFIM\n");
  printf ("\n");
  
  return 0;
}
