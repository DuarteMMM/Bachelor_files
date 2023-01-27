/* **************************************************************************
*                                                                           *
*              Série 1 (14/10/2019), exercício 4 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
*                                                                           *
************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  printf("\n*-*-*-*-*-*-*-* TENTE ADIVINHAR O NÚMERO! *-*-*-*-*-*-*-*\n\n");
  
  //Declaração de varáveis e atribuição de valores//
  
  int a, b, d, e, teste, teste1, teste2, tentativas;
  float x;
  tentativas = 0;
  printf ("Digite um número inteiro superior ou igual a 1000:\n");
  teste = scanf("%d", &a);

  //Teste da leitura do valor a//
  
  if ((teste!=1) || (a<1000))
    {
      printf("ERRO: Digitou um valor inválido.\n\n");
      return 1;
    }

  //Ciclo de gerar o número inteiro aleatório//
  
  while (2)
    {
      srand (time (NULL));
      x = (((double)rand())/((double)RAND_MAX))*a;
      b = (int)x;

      //Ciclo de tentativas//

      while (1)
	{
	  printf("\nTente adivinhar o número inteiro, entre zero (inclusive)  e o número que digitou (inclusive), no qual estou a pensar!\n");
	  teste1 = scanf("%d", &d);

	  //Teste da leitura do número digitado//
	  
	  if (teste1==0)
	    {
	      printf ("Digitou um valor inválido.\n");
	      return 2;
	    }

	  //Comparação do valor digitado com o número aleatório//
	  
	  else
	    {
	      //Valores iguais//
	      
	      if (b==d)
		{
		  printf ("Adivinhou! Muitos parabéns!\n");
		  printf ("Realizou %d tentativa(s) errada(s).\n", tentativas);
		  printf ("\nDeseja jogar de novo? [0] Sim ou [1] Não ?\n");
		  teste2 = scanf ("%d", &e);
		  
		  //Testar a leitura da escolha (continuar ou não a jogar)//
		  
		  if (teste2 == 0)
		    {
		      printf ("\nDigitou algo inválido.\n\n");
		      return 3;
		    }

		  else
		    {
		      if (e==0)
			break;     //Continuar o jogo, saindo deste ciclo, para gerar um novo número aleatório//
		      if (e==1)
			printf ("\nMuito obrigado por jogar!\n\n");
		      return 4;     //Parar o jogo//
		    }
		}

	      //Valor digitado é superior//

	      if (b>d)
		{
		  printf ("Não acertaste! Escolheste um número inferior! Tenta de novo.\n");
		  tentativas+=1;
		}

	      //Valor digitado é inferior//

	      if (b<d)
		{
		  printf ("Não acertaste! Escolheste um número superior! Tenta de novo.\n");
		  tentativas+=1;
		}
	    }
	}
    }
}

      
  
