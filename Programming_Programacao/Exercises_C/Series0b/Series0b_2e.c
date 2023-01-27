#include <stdio.h>
int main ()
{
  while (1)
    {
      float c, f;
      int a;
      printf ("Deseja converter graus Celsisus em Fahrenheit ou Fahrenheit em Celsisus?\n");
      printf ("[1] - Graus Celsius em Fahrenheit\n");
      printf ("[2] - Graus Fahrenheit em Celsius\n");
      printf ("NÃO introduza um carater não inteiro!\n");
      scanf ("%d", &a);
      while (getchar()!='\n');
      {
	if (a==1)
	  {
	    printf ("Introduza a temperatura em graus Celsius: \n");
	    scanf ("%f", &c);
	    if (c>=-273.15)
	      {
		f = c*1.8+32;
		printf ("%.4f graus Celsius equivalem a %.4f graus Fahrenheit.\n", c, f);
	      }
	    else
	      printf ("Valor inválido.\n");
	  }
	if (a==2)
	  {
	    printf ("Introduza a temperatura em graus Fahrenheit: \n");
	    scanf ("%f", &f);
	    if (f>=-459.67);
	    {
	      c = (f-32)/1.8;
	      printf ("%.4f graus Fahrenheit equivalem a %.4f graus Celsius.\n", f, c);
	    }
	    else
	      printf ("Valor inválido.\n");
	  }
	if ((a!=1) && (a!=2))
	  printf ("Introduziu uma opção inválida.\n");
      }
      int b;
      printf ("Deseja continuar?\n");
      printf ("[1] - Sim\n");
      printf ("[2] - Não\n");
      scanf ("%d", &b);
      if (b==2)
	break;
    }
  return 0;
}
