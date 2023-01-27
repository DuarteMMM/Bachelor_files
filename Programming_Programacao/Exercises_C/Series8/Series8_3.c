/* ***************************************************************************
 *                                                                           *
 *              Série 8 (02/12/2019), exercício 3 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
  int  n              ;  // Número de linhas
  char *ptr           ;  // Teste de leitura de n
  FILE *f1            ;  // Ficheiro de leitura e escrita em binário
  int  comb [100]     ;  // Vetor com elementos de linhas
  int  n1             ;  // Contador (no cálculo de elementos) e valor utilizado para ler do ficheiro
  int  k              ;  // Valor utilizado no cálculo de combinações e leituras do ficheiro
  int  n2             ;  // Contador para cálculo de elementos
  int  teste          ;  // Teste das leituras
  int  pos            ;  // Para posicionamento com fseek
  int  escolha        ;  // 'Sim' ou 'Não'
  int  i, j           ;  // Contadores para leituras do ficheiro
  int  x              ;  // Valor lido do ficheiro


  // Verificar quantos argumentos foram digitados no terminal
  
  if (argc != 2)
    {
      printf ("\n *-*-*-*-* Triângulo de Pascal de N linhas*-*-*-*-*\n");
      printf ("\nERRO: Deve digitar './[nome do programa] N', sendo N o número de linhas.\n");
      printf ("\nPara valores de N demasiado elevados, o Triângulo de Pascal não será possível de desenhar corretamente no terminal.\n\n");
      return 1;
    }
  
  // Teste e leitura do valor de n da linha de comandos
    
  n = strtol (argv [1], &ptr, 10);
    
  if ( ((*ptr) != 0) || (n <= 0) || (n > 100) )
    {
      printf ("\n *-*-*-*-* Triângulo de Pascal de N linhas *-*-*-*-*\n");
      printf ("\nERRO: Não foi possível ler o valor de N. Por favor, insira um número natural (inferior a 101).\n");
      printf ("\nPara valores de N demasiado elevados, não será possível desenhar o Triângulo de Pascal corretamente no terminal.\n\n");
      return 2;
    }

  sscanf (argv [1], "%d", &n);  // Atribuição do valor digitado (N) à variável 'n'

    
  // Abertura do ficheiro e respetivo teste
    
  f1 = fopen ("Pascal.bin", "wb+");
  if (f1 == NULL)
    {
      printf("\nERRO: Não foi possível abrir o ficheiro.\n\n");
      return 3;
    }
    
  // Construção do Triângulo de Pascal 

  printf ("\n");
  
  for (n1 = 0; n1 < n ; n1++)
    {
      k = 1; // Fixar o valor para um novo ciclo
      
      comb [0] = 1 ; // Primeiro elemento da linha é 1
      comb [n1] = 1; // Último elemento da linha é 1

      for (n2 = n1 + 1; n2 < n ; ++n2)
	printf ("   ");  // Escrever separação entre valores

      // Se não for a 1ª nem a 2ª linhas, calculam-se os valores (os que serão diferentes de 1)
      
      if (n1 > 1)
	{
	  for (n2 = 1; n2 < n1 ; n2++)
	    {
	      comb [n2] = (comb [n2 - 1] * (n1 + 1 - k) ) / k; // Calcular o valor
	      k ++;  // Avançar para o próximo valor da linha
	    }
	}

      // Escrever os valores no terminal e no ficheiro
      
      for (n2 = 0; n2 <= n1; ++n2)
	{
	  printf ("%-4d  ", comb [n2]);  // Terminal

	  // Função fwrite e respetivo teste
	  
	  teste = fwrite (&comb [n2], sizeof (int), 1, f1);
	  if (teste != 1)
	    {
	      printf ("\nERRO: A função 'fwrite' não funcionou corretamente.\n\n");
	      fclose (f1);
	      return 4;
	    }
	}
              
      printf ("\n");
    }

  // Perguntar ao utilizador se deseja saber elemento(s) do Triângulo de Pascal

  while (1)
    {
      pos = 0; // Retomar o valor zero, para um novo ciclo
      
      printf("\n\nQual a combinação de n elementos k a k que deseja saber?");

      printf ("\nIntroduza o valor de n:\n");

      // Leitura dos valores de n e k e respetivos testes
      
      teste = scanf ("%d", &n1);

      if ( (teste != 1) || (n1 < 0) || (n1 >= n) )
	{
	  printf("\nERRO: Insira valores inteiros não negativos, com n menor que N (número de linhas).\n");
	  printf ("O programa também termina se tiver digitado um valor real (de parte inteira 1 ou 2), na escolha anterior ('Sim'/'Não').\n\n");
	  fclose (f1);
	  return 5;
	}
        
      printf("Introduza o valor de k:\n");
        
      teste = scanf ("%d", &k);
        
      if ( (teste != 1) || (n1 < k) || (k < 0) )
	{
	  printf("\nERRO: Insira valores inteiros não negativos, com k menor ou igual que n.\n\n");
	  fclose (f1);
	  return 6;
	}

      // Avançar posições necessárias nas linhas anteriores
      
      for (i = 0 ; i < n1 ; i++)
	{
	  for (j = 0 ; j <= i ; j++)
	    pos += 1;
	}

      pos += k ; // Avançar na última linha em causa

      // Posicionamento no ficheiro e respetivo teste
      
      teste = fseek (f1, pos*sizeof(int), SEEK_SET);

      if (teste != 0)
	{
	  printf ("\nERRO: A função 'fseek' não funcionou corretamente.\n\n");
	  fclose (f1);
	  return 7;
	}

      // Leitura do ficheiro e respetivo teste
      
      teste = fread (&x, sizeof(int), 1, f1);

      if (teste != 1)
	{
	  printf ("\nERRO: A função 'fread' não funcionou corretamente.\n\n");
	  fclose (f1);
	  return 8;
	}
      
      printf("O valor da combinação é %d.\n", x);  // Escrever valor no terminal

      // Perguntar se se deseja continuar; testar o valor digitado
      
      printf("\n\nDeseja saber o valor de outra combinação?\n[1] Sim ;\n[2] Não .\n");
      teste = scanf ("%d", &escolha);
        
      if ( (teste == 0) || (escolha > 2) || (escolha < 1) )
	{
	  printf ("\nDigitou algo inválido. Deve selecionar o número 1 ou o número 2.\n");
	  printf ("O programa também termina se tiver digitado certos valores reais não inteiros para k.\n\n");
	  return 9;
	}

      if (escolha == 2)
	break;   
    }

  // Finalizar o programa
  
  printf ("\n-FIM-\n\n");
  fclose (f1);
  return 0;
}
