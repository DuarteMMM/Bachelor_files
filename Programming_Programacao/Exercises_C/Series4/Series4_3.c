/* **************************************************************************
*                                                                           *
*              Série 4 (04/11/2019), exercício 3 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// Função que calcula o número de algarismos

int nr_algarismos (long int maximo)
{   
  int total = 0 ;  // Número de algarismos

  while (1)
    {
      total += 1;             // Somar 1 ao número total de algarismos
      maximo = maximo / 10;   // Parte inteira da divisão por 10
      
      // Se a parte inteira for zero, não há mais algarismos a contabilizar
      
      if (maximo == 0)
	break;
    }

  return total;
}

// Função que determina se o número é ou não de Armstrong

int armstrong (long int maximo)
{
  long int soma_potencias = 0   ;  // Soma das potências dos algarismos
  int      resto                ;  // Restos das divisões (são os algarismos)
  int      i = 1                ;  // Contador
  int      total                ;  // Número de algarismos
 
  int      resultado = 0        ;  // Para saber, no fim, se é ou não número de Armstrong

  long int maximo2              ;  // Para guardar o valor "maximo" para comparação no final

  maximo2 = maximo;

  total = nr_algarismos (maximo);  // Utilizar a função anterior

  // Nota: tive problemas com o "pow", logo fiz de outra forma para obter potências

  int      j = 1             ;  // Contador para potências
  long int pot_algarismo = 1 ;  // Potências dos algarismos    
  
  while (i <= total)
    {  
      resto = maximo % 10;   // Calcular restos das divisões (são os algarismos em si)

      maximo = maximo / 10;  // Para, no próximo ciclo considerar sem o algarismo "resto" de agora

      // Calcular a potência do algarismo
      
      while (j <= total)
	{
	  pot_algarismo = pot_algarismo * resto;
	  j += 1;
	}

      j = 1;  // Fixar, de novo, o valor, para um novo ciclo

      soma_potencias = soma_potencias + pot_algarismo; // Elevar o algarismo a "total" e somar ao total das somas das potências

      i += 1;

      pot_algarismo = 1;  // Fixar, de novo, o valor, para um novo ciclo
    }

  // Se for número de Armstrong, fica 1 em "resultado"
  
  if (soma_potencias == maximo2)
    resultado = 1;

  return resultado;
}
      
int main ()
{
  long int          maximo               ;  // Valor máximo
  int               teste                ;  // Teste da sua leitura
  FILE              *f1                  ;  // Ficheiro de escrita
  long int i = 1                         ;  // Contador
  int               armstrong_sim_nao    ;  // Resultado da função "armstrong"

  // Abertura do ficheiro e respetivo teste
  
  f1 = fopen ("Números de Armstrong", "wt");
  if (f1 == NULL)
    {
      printf ("\nERRO: O ficheiro não abriu corretamente.\n");
      printf ("\n");
      fclose (f1);
      return 1;
    }
  
  printf ("\n *-*-*-*-* Números de Armstrong *-*-*-*-*\n");

  printf ("\nQual o valor máximo para os números testados?\n");
  teste = scanf ("%ld", &maximo);

  if ((teste != 1) || (maximo <= 0))
    {
      printf ("\nDigitou um valor inválido. Deve apresentar um número positivo (considerar-se-á a sua parte inteira).\n");
      printf ("\n");
      fclose (f1);
      return 2;
    }

  fprintf (f1, " *-*-*-*-* Números de Armstrong *-*-*-*-*\n");
  fprintf (f1, "\nValor máximo:%ld\n", maximo);
  fprintf (f1, "\nNúmeros de Armstrong até %ld:\n", maximo);

  printf ("\nNúmeros de Armstrong até %ld:\n", maximo);
      
  while (i <= maximo)
    {
      armstrong_sim_nao = armstrong (i);  // Ver se o número é ou não de Armstrong

      // Quando é número de Armstrong, fazer prints e somar 1 ao total desses números
      
      if (armstrong_sim_nao == 1)
	{
	  printf ("\n%ld", i);
	  fprintf (f1, "\n%ld", i);
	}

      i += 1;
    }

  printf ("\n");
  printf ("\n -FIM-\n");
  printf ("\n");

  fprintf (f1, "\n");
  fprintf (f1, "\n -FIM-\n");

  return 0;
}
