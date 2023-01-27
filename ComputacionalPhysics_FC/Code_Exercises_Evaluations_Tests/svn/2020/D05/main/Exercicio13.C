/******************************************************
 *                Física Computacional                *
 *                    Exercício 13                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <cstdio> 
#include <cmath> 

double altura_satelite (double T)
{
  double G = 6.67e-011;
  double M = 5.97e+24;
  double R = 6371000.0;
  double intermedio, altura_satelite;

  intermedio = (G*M*T*T)/(4*(M_PI)*(M_PI));
  altura_satelite = pow (intermedio, 0.333)-R;

  return altura_satelite;
}

  
int main ()
{
  double periodo, altura;
  int teste_periodo;
  printf ("\n-=-=-=- Calcular altura do satélite a partir do período -=-=-=-\n\n");
  printf ("Digite o período do satélite, em segundos: ");
  teste_periodo = scanf ("%lf", &periodo);

  if ( (teste_periodo != 1) || (periodo < 0.00000000000001) )
    {
      printf ("\n\nDigitou um valor inválido.\n\n");
      return 1;
    }

  altura = altura_satelite (periodo);
  
  printf ("\nA altura do satélite é (aproximadamente) %.3lf metros.\n", altura);

  if (altura < 0.00000001)
    printf ("\nNão é possível o satélite estar em órbita com este período.\n\n");

  return 0;
}

/*Resposta à alínea c:
  Alturas (aproximadas) dos satélites que orbitam a Terra...

...uma vez por dia (T = 24h = 86400 segundos): 35120937.508 metros;
...a cada 90 minutos = 5400 segundos: 175660.304 metros;
...a cada 45 minutos = 2700 segundos: -2244956.241 metros. 

Comentários: maior período implica menor raio de órbita; é impossível um satélite orbitar  Terra com uma órbita de período 45 minutos. */

  
