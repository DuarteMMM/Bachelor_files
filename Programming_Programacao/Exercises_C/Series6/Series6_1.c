/* ***************************************************************************
 *                                                                           *
 *              Série 6 (18/11/2019), exercício 1 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */

#include <stdio.h>
#include <math.h>

// Funções não definidas em C

double funcao2 (double x)
{
  return cos(4*x);
}

double funcao8 (double x)
{
  return exp(6*x);
}

double funcao9 (double x)
{
  return 4*cos(2*x)*sin(3*x);
}

// Funções derivadas não definidas em C

double deriv2 (double x)
{
  return (-4)*sin(4*x);
}
double deriv3 (double x)
{
  return 1+tan(x)*tan(x);
}

double deriv4 (double x)
{
  return 1/sqrt(1+x*x);;
}

double deriv5 (double x)
{
  return -1/sqrt(1+x*x);
}

double deriv6 (double x)
{
  return 1/x;
}

double deriv7 (double x)
{
  return 1/(x*log(10));
}

double deriv8 (double x)
{
  return 6*exp(6*x);
}

double deriv9 (double x)
{
  return 4*(-2*sin(2*x)*sin(3*x)+3*cos(2*x)*cos(3*x));
}


// Função da derivada

double derivada_func (double (*funcao)(double), double x)
{
  double h = 1.e-6          ; // h (foi escolhido um valor suficientemente pequeno, mas não em excesso)

  double derivada; // Derivada no ponto

  derivada = (funcao (x+h) - funcao (x)) / h;

  return derivada;
}

// Main

int main ()
{
  int    escolha       ; // Número do menu
  int    c             ; // Para continuar ou parar o ciclo
  int    teste1        ; // Teste da leitura da escolha
  int    teste3        ; // Teste da leitura de c
  double ponto         ; // Ponto para cálculo da derivada
  int    teste2        ; // Teste da leitura de inf
  double derivada      ; // Valor da derivada
  double derivada_real ; // Valor real da derivada
  double erro          ; // Erro percentual

  printf ("\n*-*-*-*-* Derivadas de funções *-*-*-*-*\n"); // Título

  while (1)
    {
      // Leitura do número do menu e respetivo teste
      printf ("\nLista de Funções:\n1. sin(x)          ;\n2. cos(4x)         ;\n3. tan(x)          ;\n4. arcsin(x)       ;\n5. arccos(x)       ;\n6. ln(x)           ;\n7. log(x)          ;\n8. exp(6*x)        ;\n9. 4cos(2x)sin(3x) .\n");
      printf ("\nSelecione uma das opções:\n");
      teste1 = scanf ("%d", &escolha);
      if ( (teste1 != 1) || (escolha < 1) || (escolha > 9) )
	{
	  printf ("\nERRO: Deve digitar um valor da lista. Se digitar um número real, é considerada a respetiva parte inteira.\n\n");
	  return 1;
	}

      // Leitura do ponto onde calcular a derivada
      printf ("\nDigite o ponto no qual quer calcular a derivada:\n");
      teste2 = scanf ("%lf", &ponto);
      if (teste2 != 1)
	{
	  printf ("\nERRO: Deve apresentar um número real.\n\n");
	  return 2;
	}

      // Cálculo do integral
  
      if (escolha == 1)
	{
	  derivada = derivada_func (sin, ponto);
	  derivada_real = cos(ponto);
	}

      if (escolha == 2)
	{
	  derivada = derivada_func (funcao2, ponto);
	  derivada_real = deriv2 (ponto);
	}

      if (escolha == 3)
	{
	  derivada = derivada_func (tan, ponto);
	  derivada_real = deriv3 (ponto);
	}

      if (escolha == 4)
	{
	  if ((ponto > 1) || (ponto < -1) )
	    {
	      printf ("\nINVÁLIDO: A função arcsen(x) só admite valores entre -1, inclusive, e 1, inclusive.\n");
	      printf ("\n -FIM-\n\n");
	      return 3;
	    }

	  if ((ponto <= 1) && (ponto >= -1) )
	    {
	      derivada = derivada_func (asin, ponto);
	      derivada_real = deriv4 (ponto);
	    }
	} 

      if (escolha == 5)
	{
	  if ((ponto > 1) || (ponto < -1) )
	    {
	      printf ("\nINVÁLIDO: A função arccos(x) só admite valores entre -1, inclusive, e 1, inclusive.\n");
	      printf ("\n -FIM-\n\n");
	      return 4;
	    }

	  if ((ponto <= 1) && (ponto >= -1) )
	    {
	      derivada = derivada_func (acos, ponto);
	      derivada_real = deriv5 (ponto);
	    }
	} 

      if (escolha == 6)
	{
	  if (ponto <= 0)
	    {
	      printf ("\nINVÁLIDO: A função ln(x) só admite valores positivos.\n");
	      printf ("\n -FIM-\n\n");
	      return 5;
	    }

	  if (ponto > 0)
	    {
	      derivada = derivada_func (log, ponto);
	      derivada_real = deriv6 (ponto);
	    }
	} 

      if (escolha == 7)
	{
	  if (ponto <= 0)
	    {
	      printf ("\nINVÁLIDO: A função log(x) só admite valores positivos.\n");
	      printf ("\n -FIM-\n\n");
	      return 6;
	    }

	  if (ponto > 0)
	    {
	      derivada = derivada_func (log10, ponto);
	      derivada_real = deriv7 (ponto);
	    }
	}

      if (escolha == 8)
	{
	  derivada = derivada_func (funcao8, ponto);
	  derivada_real = deriv8 (ponto);
	}
  
      if (escolha == 9)
	{
	  derivada = derivada_func (funcao9, ponto);
	  derivada_real = deriv9 (ponto);
	}

    
      // Apresentar os valores e finalizar o programa
  
      printf ("\nValor calculado da derivada : %.10lf\n", derivada);
      printf ("\nValor verdadeiro da derivada: %.10lf\n", derivada_real);

      erro = ((derivada - derivada_real) / derivada_real) * 100;
      printf ("\nO erro percentual do valor obtido é o seguinte: %lf\n", erro);

      printf ("\nDeseja continuar?\n(1)Sim;\n(2)Não.\n\n");
      teste3 = scanf ("%d", &c);

      if ((teste3 != 1) || (c<1) || (c>2))
	{
	  printf ("\nERRO: Deve digitar o número 1 ou o número 2.\n");
	  printf ("\n -FIM-\n\n");
	  return 7;
	}

      if (c == 2)
	break;
    }
  
  printf ("\n -FIM-\n\n");
 
  return 0;
}
