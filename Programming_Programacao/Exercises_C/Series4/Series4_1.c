/* **************************************************************************
*                                                                           *
*              Série 4 (04/11/2019), exercício 1 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ()
{
  double valor ;  // Valores da sucessão
  int    teste ;  // Teste da leitura do primeiro valor da sucessão 
  FILE   *f1   ;  // Ficheiro de escrita
  int    i = 1 ;  // Contador
  double ptr  ;  // Ponteiro para inteiro (obrigatório colocar na função modf)

  // Abertura do ficheiro e seu teste
  
  f1 = fopen ("Bernoulli.dat", "wt");

  if (f1 == NULL)
    {
      printf ("\nERRO: O ficheiro não abriu corretamente.\n");
      fclose (f1);
      printf ("\n");
      return 1;
    }

  // Leitura do primeiro valor e seu teste

  printf ("\n *-*-*-*-* Função de Bernoulli *-*-*-*-*\n");
  printf ("\nDigite o primeiro valor da sucessão:\n");
  teste = scanf ("%lf", &valor);

  if (teste != 1)
    {
      printf ("\nDigitou um valor inválido. Deve apresentar um número real.\n");
      printf ("\n");
      fclose (f1);
      return 2;
    }

  fprintf (f1, " *-*-*-*-* Função de Bernoulli *-*-*-*-*\n");
  fprintf (f1, "\nPrimeiro valor:%10lf\n", valor);
  printf ("\nNúmero da iterada       Valor");
  fprintf (f1, "\nIterada         Valor");


  // Cálculo e escrita das iteradas
  
  while (i < 101)
    {
      valor = modf (2.0*valor, &ptr);   // Guardar em "valor" a parte fracionária de 2 x valor

      // Escrita dos valores obtidos
      
      printf ("\n      %3d           %10lf", i, valor);
      fprintf (f1, "\ni =%3d      %10lf", i, valor);
      i += 1;
    }

  // Terminar o programa

  printf ("\n");
  printf ("\n -FIM-\n");
  printf ("\n");

  fprintf (f1, "\n");
  fprintf (f1, "\n -FIM-");
  fclose (f1);

  return 0;
}
      
