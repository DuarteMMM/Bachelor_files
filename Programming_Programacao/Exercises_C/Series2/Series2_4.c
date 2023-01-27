/* **************************************************************************
*                                                                           *
*              Série 2 (21/10/2019), exercício 4 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */


#include <stdio.h>

// Declaração da estrutura //

struct hora{
  char nome [33];    // Nome da informação horária //
  int h;             // Valor das horas //
  int m;             // Valor dos minutos //
  int s;             // Valor dos segundos //
};

// NOTA: colocou-se um tamanho de 33 porque "soma das informações horárias, o "maior texto", precisa de 33 espaços.

int main (int argc, char **argv)
{
  // Declaração das variáveis //
    
  int h1, m1, s1, h2, m2, s2;    // Horas, minutos e segundos para as duas informações horárias //
  int seg1, seg2;                // Número de segundos totais //
  float min1, min2;              // Número de minutos totais //
  int soma_h, soma_m, soma_s;    // Soma das informações horárias //
  int teste1, teste2;            // Testes de leituras //
    
  // Instrução caso o utilizador não coloque duas informações horárias corretamente //
    
  if (argc != 3)
    {
      printf ("\nERRO: Insira duas informações horárias h:m:s, separadas por um espaço em branco.\n");
      printf ("\n");
      return 1;
    }
    
  // Leituras da linha de comandos e testes//
    
  teste1 = sscanf (argv[1], "%d:%d:%d\n", &h1, &m1, &s1);
  teste2 = sscanf (argv[2], "%d:%d:%d\n", &h2, &m2, &s2);
    
  if ((teste1 != 3) || (teste2 != 3) || (h1 % 1 != 0) || (m1 % 1 != 0) || (s1 % 1 != 0) || (h2 % 1 != 0) || (m2 % 1 != 0) || (s2 % 1 != 0))
    {
      printf ("\nERRO: Insira duas informações horárias h:m:s, separadas por um espaço em branco.\n");
      printf ("\n");
      return 2;
    }

  // Atribuição de dados à estrutura //
  
  struct hora x1 = {"1ª informação horária", h1, m1, s1};
  struct hora x2 = {"2ª informação horária", h2, m2, s2};
    
  // Restrições aos valores inseridos nas informações horárias, recorrendo à estrutura //

  if ((x1.h < 0) || (x1.h > 23) || (x1.m < 0) || (x1.m > 59) || (x1.s < 0) || (x1.s > 59) || (x2.h < 0) || (x2.h > 23) || (x2.m < 0) || (x2.m > 59) || (x2.s < 0) || (x2.s > 59))
    {
      if ((x1.h < 0) || (x1.h > 23) || (x1.m < 0) || (x1.m > 59) || (x1.s < 0) || (x1.s > 59))
	  printf ("\nInseriu uma primeira informação horária inválida.\n");
      if ((x2.h < 0) || (x2.h > 23) || (x2.m < 0) || (x2.m > 59) || (x2.s < 0) || (x2.s > 59))
	  printf ("\nInseriu uma segunda informação horária inválida.\n");
      
      printf ("\n");
      return 3;
    }
    
  // Impressão das informações horárias //

  printf ("\n*-*-*-*-* Informações horárias *-*-*-*-*\n");
    
  printf ("\n%s\n%d h : %d min : %d s\n", x1.nome, x1.h, x1.m, x1.s);
  printf ("\n%s\n%d h : %d min : %d s\n", x2.nome, x2.h, x2.m, x2.s);
    
  // Apresentação das informações horárias em segundos //
    
  seg1 = x1.s + x1.m * 60 + x1.h * 60 * 60;
  printf ("\nO número de segundos que equivale à %s é %d.\n", x1.nome, seg1);
  seg2 = x2.s + x2.m * 60 + x2.h * 60 * 60;
  printf ("\nO número de segundos que equivale à %s é %d.\n", x2.nome, seg2);
    
  // Apresentação das informações horárias em minutos //
    
  min1 = x1.m + x1.h * 60 + ((float) x1.s) / 60;
  printf ("\nO número de minutos que equivale à %s é aproximadamente %.2f.\n", x1.nome, min1);
  min2 = x2.m + x2.h * 60 + (float) x2.s / 60;
  printf ("\nO número de minutos que equivale à %s é aproximadamente %.2f.\n", x2.nome, min2);
    
  // Soma das duas informações horárias //
    
  soma_h = x1.h + x2.h;
  soma_m = x1.m + x2.m;
  soma_s = x1.s + x2.s;
    
  // Operações a realizar para a apresentação correta dos valores da soma das informações horárias //
    
  while (soma_h > 23)
    {
      soma_h = soma_h - 24;
    }
    
  while (soma_m > 59)
    {
      soma_m = soma_m - 60;
      soma_h = soma_h + 1;
    }
    
  while (soma_s > 59)
    {
      soma_s = soma_s - 60;
      soma_m = soma_m + 1;
    }
    
  // Apresentação da soma das informações horárias através da estrutura //
    
  struct hora x3 = {"soma das informações horárias", soma_h, soma_m, soma_s};
  printf ("\nA %s é %d h : %d min : %d s.\n", x3.nome, x3.h, x3.m, x3.s);

  printf ("\n");
    
  return 0;
}
