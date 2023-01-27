/* **************************************************************************
 *                                                                           *
 *              Série 5 (11/11/2019), exercício 1 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 ************************************************************************** */
# include <stdio.h>

// Função de conversão para binário

void binario (int numero, char *resultado)
{
  int r ;   // Restos das divisões por 2
  int i ;   // Contador

  // Ciclo de cálculo do binário (8 repetições porque o binário terá 8 algarismos)
  
  for (i = 0; i < 8; ++i)
    {
      r = numero % 2              ;   // Resto
      resultado [7 - i] = '0' + r ;   // Quando r=0, soma-se zero a essa posição da tabela ASCII -> '0'; quando r=1, soma-se uma posição -> '1'
      numero = numero / 2         ;   // Quociente e (possivelmente) próximo dividendo
    }

  /* NOTA: vão-se atribuindo valores a "resultado [7-i]" para guardar os restos, no vetor, na ordem inversa à qual são calculados.
     Assim, escreve-se o número em binário. */
  
  resultado [8] = 0;   // Atribuir o terminador à última posição
}

// Função de conversão para octal

void octal (int numero, char *resultado)
{
  int r     ;   // Restos das divisões por 8
  int i = 0 ;   // Contador
  int valor ;   // Algarismo "guardado"

  // Na base octal, para não haver zero(s) à esquerda, divide-se em dois casos e far-se-á o ciclo 'while' enquanto numero>0
  
  if (numero == 0)
    {
      resultado [0] = '0';
      i = 1;                // Atribui-se 1 a i para atribuir o terminador a essa posição, no final desta função
    }

  else
    {
      // Calcular os algarismos na base octal

      while (numero > 0)
	{
	  r = numero % 8;
	  resultado [i] = '0' + r;
	  numero = numero / 8;

	  i += 1;
	}

      // O número terá 1, 2 ou 3 algarismos (i é essa quantidade); se i>1, troca-se a ordem

      if (i > 1)
	{

	  // Trocar a ordem dos algarismos

	  valor = resultado [0];               // Guardar o primeiro valor

	  // Trocar a ordem do 1º algarismo (posição 0) com o último (posição i-1)
      
	  resultado [0] = resultado [i - 1];  
	  resultado [i - 1] = valor;
	}
    }

  resultado [i] = 0;          // Terminador
}

// Função de conversão para hexadecimal

void hexadecimal (int numero, char *resultado)
{
  int r     ;   // Restos das divisões por 16
  int i = 0 ;   // Contador
  int valor ;   // Algarismo "guardado" para troca

  // Para não haver zero(s) à esquerda, divide-se em dois casos e far-se-á o ciclo 'while' enquanto numero>0
  
  if (numero == 0)
    {
      resultado [0] = '0';
      i = 1;
    }

  else
    {
      while (numero > 0)
	{
	  // Calcular os algarismos na base hexadecimal

	  r = numero % 16;   // Resto da divisão

	  // No caso do resto não ser superior a 9, o algarismo é um número

	  if (r <= 9)
	    resultado [i] = '0' + r;

	  // No caso do resto ser superior a 9, o "algarismo" é uma letra de 'A' a 'E'

	  else
	    resultado [i] = 'A' + (r - 10);   // Avança-se 0,1,2,3,4 ou 5 posições na tabela ASCII, relativamente ao 'A'

	  numero = numero / 16;

	  i += 1;
	}
      
      // Só pode haver 1 ou 2 "algarismos", no total ("i" é, agora, o número de "algarismos")

      if (i == 2)
	{
	  // Trocar a ordem dos 2 algarismos

	  valor = resultado [0];               // Guardar o primeiro valor

	  // Trocar a ordem
      
	  resultado [0] = resultado [1];  
	  resultado [1] = valor;
	}
    }

  resultado [i] = 0;  // Terminador
}

int main ()
{
  int i                                            ;   // Contador e números em base decimal
  char resposta1 [9], resposta2 [4], resposta3 [3] ;   // Vetores para binario, octal e hexadeximal, respetivamente

  printf ("\n *-*-*-*-* Conversão entre bases *-*-*-*-*\n");

  printf ("\n Decimal    Binário      Octal   Hexadecimal\n");

  // Executar as funções para números inteiros de 0 a 255 e mostrar os resultados no ecrã
  
  for (i = 0 ; i <= 255 ; ++i)
    {
      binario (i, resposta1);
      octal (i, resposta2);
      hexadecimal (i, resposta3);
      printf ("  %3d      %8s      %3s        %2s\n",i ,resposta1 ,resposta2 ,resposta3);
    }

  // Terminar o programa
  
  printf ("\n -FIM-\n");
  printf ("\n");

  return 0;
}
