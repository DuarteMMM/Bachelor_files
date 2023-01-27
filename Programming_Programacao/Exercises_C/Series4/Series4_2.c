/* **************************************************************************
*                                                                           *
*              Série 4 (04/11/2019), exercício 2 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct
{
  double Re;
  double Im;
} Complexo;

void help ()
{
  printf ("\nERRO: Deve digitar de acordo com uma das seguintes opções:\n");
  printf ("\n (1) Módulo    : './[nome do programa] mod [Re(x)] [Im(x)]';\n");
  printf ("\n (2) Adição    : './[nome do programa] + [Re(x)] [Im(x)] [Re(y)] [Im(y)]'\n");
  printf ("\n (3) Diferença : './[nome do programa] - [Re(x)] [Im(x)] [Re(y)] [Im(y)]'\n");
  printf ("\n (4) Produto   : './[nome do programa] x [Re(x)] [Im(x)] [Re(y)] [Im(y)]'\n");
  printf ("\n (5) Divisão   : './[nome do programa] / [Re(x)] [Im(x)] [Re(y)] [Im(y)]'\n");

  printf ("\n");
  
  exit (-1);
}

// Módulo

double Cmod (Complexo *z)
{
  double mod;

  mod = (z->Re * z->Re) + (z->Im * z->Im); 
  mod = sqrt (mod);

  return mod;
}

// Soma

void Cadd (Complexo *f, Complexo *z1, Complexo *z2)
{
  f->Re = z1->Re + z2->Re;
  f->Im = z1->Im + z2->Im;
}

// Subtração

void Csub (Complexo *f, Complexo *z1, Complexo *z2)
{
  f->Re = z1->Re - z2->Re;
  f->Im = z1->Im - z2->Im;
}

// Produto

void Cpro (Complexo *f, Complexo *z1, Complexo *z2)
{
  f->Re = (z1->Re * z2->Re) - (z1->Im * z2->Im);
  f->Im = (z1->Re * z2->Im) + (z2->Re * z1->Im);
}

// Divisão

void Cdiv (Complexo *f, Complexo *z1, Complexo *z2)
{
  f->Re = ((z1->Re * z2->Re) + (z1->Im * z2->Im)) / ((z2->Re * z2->Re)+ (z2->Im * z2->Im));
  f->Im = ((z2->Re * z1->Im) - (z1->Re * z2->Im)) / ((z2->Re * z2->Re)+ (z2->Im * z2->Im));}

// Escrita dos complexos no terminal

void Cprint (Complexo *z)
{
  printf ("(%lf", z->Re);            // Parte real

  if (z->Im >= 0)
    printf ("+%lf i)", z->Im);       // Parte imaginária positiva ou nula

  else if (z->Im < 0)
    printf ("%lf i)", z->Im);        // Parte imaginária negativa (não se mete o sinal '+')
}

int main (int argc, char **argv)
{
  // Declaração das variáveis
  
  double     res ;    //Resultado da operação pedida
  Complexo   r   ;    //Resultado da operação pedida
  Complexo   x   ;    //Complexo 1
  Complexo   y   ;    //Complexo 2
  int        t   ;    //Teste do sscanf

  // Teste de leituras: devem digitar-se 4 ou 6 coisas

  if (argc != 4 && argc != 6)
    help ();
  
  // Título do programa

  printf ("\n*-*-*-*-* Números complexos *-*-*-*-*\n");

  // No caso de serem digitadas 4 coisas, tem de se aplicar o módulo

  if (argc == 4)
    {
      // Testar se se escreveu "mod"
      
      if (strcmp (argv [1], "mod") != 0)
	help ();

      // Testar se se escreveram números reais
      
      else if (sscanf (argv [2], "%lf", &x.Re) != 1 || sscanf (argv [3],"%lf", &x.Im) != 1)
	help ();

      else
	{
	  res = Cmod (&x);                // Cálculo
	  printf ("\n|");
	  Cprint (&x);                    // Print do número
	  printf ("|");
	  printf (" = %lf", res);         // Print do resultado
	  printf ("\n");
	}
    }

  // No caso de serem digitadas 6 coisas

  else if (argc == 6)
    {
      // Verificar se se digitaram quatro números reais
      
      t = sscanf (argv [2], "%lf", &x.Re);
      t = t + sscanf (argv [3], "%lf", &x.Im);
      t = t + sscanf (argv [4], "%lf", &y.Re);
      t = t + sscanf (argv [5], "%lf", &y.Im);

      if (t != 4)
	help ();

      // Adição
      
      else if (strcmp (argv [1], "+") == 0)
	{
	  Cadd (&r, &x, &y);   // Cálculo
	  
	  printf ("\n");       
	  Cprint (&x);         // Print do primeiro número
	  printf (" + ");
	  Cprint (&y);         // Print do segundo número
	  printf (" = ");
	  Cprint (&r);         // Print do resultado
	  printf ("\n");
	}

      // Subtração

      else if (strcmp (argv [1], "-") == 0)
	{
	  Csub (&r, &x, &y);  // Cálculo

	  printf ("\n");
	  Cprint (&x);        // Print do primeiro número
	  printf (" - ");
	  Cprint (&y);        // Print do segundo número
	  printf (" = ");
	  Cprint (&r);        // Print do resultado
	  printf ("\n");
	}

      // Multiplicação

      else if (strcmp (argv [1], "x") == 0)
	{
	  Cpro (&r, &x, &y);  // Cálculo
	  
	  printf ("\n");  
	  Cprint (&x);        // Print do primeiro número
	  printf (" x ");
	  Cprint (&y);        // Print do segundo número
	  printf (" = ");
	  Cprint (&r);        // Print do resultado
	  printf ("\n");
	}

      // Divisão

      else if (strcmp (argv [1], "/") == 0)
	{
	  Cdiv (&r, &x, &y);  // Cálculo

	  printf ("\n");
	  Cprint (&x);        // Print do primeiro número
	  printf (" / ");
	  Cprint (&y);        // Print do segundo númer
	  printf (" = ");
	  Cprint (&r);        // Print do resultado
	  printf ("\n");
	}

      // Quando se digitou um símbolo incorreto

      else
	help ();
    }

  // Finalizar o programa

  printf ("\n *FIM*\n");
  printf ("\n");
  
  return 0;
}
