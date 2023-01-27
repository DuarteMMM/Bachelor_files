/* **************************************************************************
*                                                                           *
*               Série 1 (14/10/2019), exercício 1 - Programação             *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
*                                                                           *
************************************************************************** */                                                                       

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
  printf ("\n*-*-*-*-* Problema da Agulha de Buffon  *-*-*-*-*\n");
  
  //Declaração de variáveis e atribuição de valores//

  int teste, t, i, total;
  double x, y, r;

  total=0;
  
  printf("\nQuantos pontos deseja gerar?\n");
  
  teste = scanf("%d", &t);

  //Teste da leitura do valor pedido//
  
  if ((teste != 1) || (t<1))
    {
      printf ("Introduziu um valor inválido.\n\n");
      return 1;
    }

  else
    {
      srand(time(NULL));

      //Gerar números aleatórios e verificar se se encontram no círculo//

      for (i=0; i<t; i++)
	{
	  x=(((double)rand())/((double)RAND_MAX))-0.5;
	  y=((double)rand())/((double)RAND_MAX)-0.5;

	  if ((pow(x,2) + pow(y,2))<=0.25)
	    total = total + 1;
	}

      //Cálculo e apresentação do quádruplo da razão//

      r=((((double)total)/((double)t))*4);

      printf("A razão em causa, multiplicada por 4, é igual a %lf.\n\n", r);
    }

  return 0;

}

/* A probabilidade de um ponto do quadrado se encontrar no círculo é dada pelo quociente entre a área do círculo e a área do quadrado, ou seja, (pi*(0.25²))/1² = pi/4. À medida que o número de pontos gerados aumenta, a razão entre o número de pontos do círculo e dos pontos gerados aproxima-se desta probabilidade, logo o quádrúplo aproximar-se-á de pi. Pode, assim, verificar-se, através deste programa, a proximidade a pi dos valores de 4*razão, para um grande número de pontos gerados. */
