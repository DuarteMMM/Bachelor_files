/* ***************************************************************************
 *                                                                           *
 *              Série 7 (25/11/2019), exercício 4 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */
#include <stdio.h>
#include <math.h>

// Funções que não se encontram definidas em C

double funcao2 (double x)
{
  return 5*cos(2*x)*exp(-0.2*x);
}

double funcao4 (double x)
{
  return 7*pow(x,5.)-3*pow(x, 2.);
}

double funcao6 (double x)
{
  return 1/sqrt(M_PI)*exp(-x*x);
}

// Função do integral

double integral_func (double (*funcao)(double), double inf, double sup)
{
  double delta = 1.e-6       ; // delta_x (foi escolhido um valor suficientemente pequeno, mas não em excesso)
  double troca               ; // Valor para troca de inf e sup, se necessário

  double area_total = 0.     ; // Soma das áreas dos retângulos
  int verificar_se_troca = 0 ; // Para verificar se se trocaram os extremos

  // Trocar a ordem de sup e inf, se necessário

  if (inf > sup)
    {
      troca = sup;
      sup = inf;
      inf = troca;

      verificar_se_troca = 1;
    }

  // Calcular o integral

  while (inf < sup)
    {
      area_total = area_total + delta * funcao (inf + (delta / 2));  // Área do retângulo
      inf += delta;
    }

  // Trocar o sinal, se os extremos tiverem sido trocados
  
  if (verificar_se_troca == 1)
    area_total = -area_total;

  return area_total;
}

// Main

int main ()
{
  int    escolha   ; // Número do menu
  int    teste1    ; // Teste da leitura da escolha
  double inf       ; // Limite inferior do integral
  int    teste2    ; // Teste da leitura de inf
  double sup       ; // Limite superior do integral
  int    teste3    ; // Teste da leitura de sup
  double integral  ; // Valor do integral

  printf ("\n*-*-*-*-* Integrais de Riemann *-*-*-*-*\n"); // Título

  // Leitura do número do menu e respetivo teste
  printf ("\nLista de Funções:\n1. sin(x)               ;\n2. 5cos(2x) x e^(-0.2x) ;\n3. sqrt(x)              ;\n4. 7x⁵ - 3x²            ;\n5. e^x                  ;\n6. 1/sqrt(Pi) x e^(-x²) .\n");
  printf ("\nSelecione uma das opções:\n");
  teste1 = scanf ("%d", &escolha);
  if ( (teste1 != 1) || (escolha < 1) || (escolha > 6) )
    {
      printf ("\nERRO: Deve digitar um valor da lista. Se digitar um número real, é considerada a respetiva parte inteira.\n\n");
      return 1;
    }

  // Leitura do limite inferior do integral e respetivo teste
  printf ("\nDigite o limite inferior do integral:\n");
  teste2 = scanf ("%lf", &inf);
  if (teste2 != 1)
    {
      printf ("\nERRO: Deve apresentar um número real.\n\n");
      return 2;
    }

  // Limite superior do integral e respetivo teste
  printf ("\nDigite o limite superior do integral:\n");
  teste3 = scanf ("%lf", &sup);
  if (teste3 != 1)
    {
      printf ("\nERRO: Deve apresentar um número real.\n\n");
      return 3;
    }

  // Cálculo do integral
  
  if (escolha == 1)
    integral = integral_func (sin, inf, sup);

  if (escolha == 2)
    integral = integral_func (funcao2, inf, sup);

  if (escolha == 3)
    {
      if ( (inf < 0.) || (sup < 0.) )
	{
	  printf ("\nINVÁLIDO: A função sqrt(x) só admite valores não negativos para o seu integral.\n");
	  printf ("\n -FIM-\n\n");
	  return 4;
	}

      if ( (inf >= 0.) && (sup >= 0.) )
	integral = integral_func (sqrt, inf, sup);
    } 

  if (escolha == 4)
    integral = integral_func (funcao4, inf, sup);

  if (escolha == 5)
    integral = integral_func (exp, inf, sup);

  if (escolha == 6)
    integral = integral_func (funcao6, inf, sup);

  // Apresentar o valor do integral e finalizar o programa
  
  printf ("\nValor do integral: %lf\n", integral);
  printf ("\n -FIM-\n\n");
 
  return 0;
}
