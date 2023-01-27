/* **************************************************************************
*                                                                           *
*              Série 3 (28/10/2019), exercício 3 - Programação              *
*                      Duarte Marques - ist196523                           *
*                      Rodrigo Simões - ist196564                           *
*                                                                           *
************************************************************************** */

#include <stdio.h>
#include <string.h>

// Estrutura com todas as categorias de características dos planetas

struct planeta
{
    char    nome [10];
    double  distancia;
    double  massa;
    double  inclinacao;
    double  raio;
    double  trevolucao;
    double  ttranslacao;
    int     satelites;
    char    anao [5];
};


// Função para ERRO

void erro ()
{
  printf ("\nERRO: Deve digitar algo relativo a uma das seguintes opções:");
  printf ("\n(1) O nome de um planeta do Sistema Solar;");
  printf ("\n(2) o nome de um planeta, seguido de uma propriedade específica;");
  printf ("\n(3) uma propriedade específica (digite [planeta] [propriedade]).\n");
  printf ("\nOs planetas são: Mercúrio, Vénus, Terra, Marte, Júpiter, Saturno, Urano, Neptuno, Plutão e Ceres;\n");
  printf ("\nAs propriedades são: Nome, Distância_média_ao_Sol, Massa, Inclinação_orbital, Raio_médio, Tempo_de_revolução, Período_de_translação, Número_de_satélites e Planeta_Anão?.\n");
  printf ("\n");
}

// Função com título

void titulo ()
{
  printf ("\n *-*-*-*-* Planetas do Sistema Solar *-*-*-*-*\n");
}

// Função ao terminar a execução do pretendido

void fim ()
{
  printf ("\n -FIM-\n");
  printf ("\n");
}


int main (int argc, char **argv)
{
  int teste;  // Testar adequação dos valores digitados no terminal
  int x;      // Contador

    if ((argc < 2) || (argc > 3))
      {
	erro ();
	return 1;
      }

    // Informações de todos os planetas
    
    struct planeta planetas [11] = {
      {"Mercúrio", 57909227,   3.301e23,   7.0,       2439.7,  58.646,     0.2408467,  0,   "Não"},
      {"Vénus",    108209475,  4.8673e24,  3.39,      6051.8,  -243.018,   0.6151973,  0,   "Não"},
      {"Terra",    149598262,  5.9722e24,  0.0,       6371,    0.997,      1,          1,   "Não"},
      {"Marte",    227943824,  6.4169e23,  1.85,      3389.5,  1.026,      1.8808,     2,   "Não"},
      {"Júpiter",  778340821,  1.90e27,    1.304,     69911,   0.4135,     11.86,      79,  "Não"},
      {"Saturno",  1.437e9,    5.6832e26,  2.49,      58232,   0.444,      29.447,     83,  "Não"},
      {"Urano",    2.871e9,    8.6810e25,  0.77,      25362,   -0.718,     84.017,     27,  "Não"},
      {"Neptuno",  4.498e9,    1.0241e26,  1.77,      24622,   0.671,      164.79,     14,  "Não"},
      {"Plutão",   5906440628, 1.309e22,   17.14175,  1188.3,  -6.387230,  248.09,     5,   "Sim"},
      {"Ceres",    413000000,  9.5e20,     122.5,     473,     0.3781,     4.599,      0,   "Sim"}
    };

    teste = 0;

    // Apenas digitada uma coisa
    
    if (argc == 2)
    {
        for (x = 0; x < 10; x++)
        {
            // Comparar a string digitada com o nome dos planetas; se for um nome de planeta, mostrar propriedades desse planeta
            
            if ( (strcmp (argv [1], planetas [x].nome) ) == 0)
	      {
		titulo ();
	      
                printf ("\nNome:                     %s ;\n", planetas [x].nome);
                printf ("Distância média ao sol:   %lg km ;\n", planetas [x].distancia);
                printf ("Massa:                    %lg kg ;\n", planetas [x].massa);
                printf ("Inclinação orbital:       %lgº ;\n", planetas [x].inclinacao);
                printf ("Raio médio:               %lg kg ;\n", planetas [x].raio);
                printf ("Tempo de revolução:       %lg dias ;\n", planetas [x].trevolucao);
                printf ("Tempo de translação:      %lg anos ;\n", planetas [x].ttranslacao);
                printf ("Número de satélites:      %d ;\n", planetas [x].satelites);
                printf ("Planeta anão?             %s .\n", planetas [x].anao);
		
		fim ();
		teste = 1;
            }
            
            //  Comparar a string digitada com o nome das propriedades; se for um nome de alguma, mostrá-la, para todos os planetas
            
            if ( (strcmp (argv [1], "Nome")) == 0)
	      {
		titulo ();
		
		printf ("\nNomes dos planetas:\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s\n", planetas [x].nome);
		
		fim ();

		teste = 1;
	      }
            
            if ( (strcmp (argv [1], "Distância_média_ao_Sol")) == 0)
	      {
		titulo ();
		
		printf ("\nDistâncias médias ao Sol:\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %lg km ;\n", planetas [x].nome, planetas [x].distancia);

		fim ();

		teste = 1;
	      }
            
            if ( (strcmp (argv [1], "Massa")) == 0)
	      {
		titulo ();
		
		printf ("\nMassas:\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %lg kg\n", planetas [x].nome, planetas [x].massa);

		fim ();

		teste = 1;
	      }
            
            if ( (strcmp (argv [1], "Inclinação_orbital")) == 0)
	      {
		titulo ();
		
		printf ("\nInclinações:\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %lgº\n", planetas [x].nome, planetas [x].inclinacao);

		fim ();

		teste = 1;
	      }
            
            if ( (strcmp (argv[1], "Raio_médio")) == 0)
	      {
		titulo ();
		
		printf ("\nRaios:\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %lg km\n", planetas[x].nome, planetas[x].raio);

		fim ();

		teste = 1;
	      }
            
            if ( (strcmp (argv [1], "Tempo_de_revolução")) == 0)
	      {
		titulo ();
		
		printf ("\nTempos:\n");
		printf ("\n");
		
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %lg dias\n", planetas[x].nome, planetas[x].trevolucao);

		fim ();
		
		teste = 1;
	      }
            
            if ( (strcmp (argv [1], "Período_de_translação")) == 0)
	      {
		titulo ();
		
		printf ("\nTempos:\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %lg anos\n", planetas[x].nome, planetas[x].ttranslacao);

		fim ();
		
		teste = 1;
	      }
            
            if ( (strcmp (argv [1], "Número_de_satélites")) == 0)
	      {
		titulo ();
		
		printf ("\nNúmero de satélites naturais:\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %d \n", planetas[x].nome, planetas[x].satelites);

		fim ();
		
		teste = 1;
	      }
            
            if ((strcmp (argv[1], "Planeta_anão?"))== 0)
	      {
		titulo ();
		
		printf ("\nPlaneta anão?\n");
		printf ("\n");
		
                for (x = 0; x < 10; x++)
		  printf ("%s : %s\n", planetas[x].nome, planetas[x].anao);

		fim ();
		
		teste = 1;
	      }
        }

	// Dar erro quando é digitado algo que não corresponde a um planeta ou uma propriedade
	
	if (teste == 0)
	  erro ();
    }
    
    // Digitar uma propriedade de um planeta quando são digitados dois argumentos (adequados)
    
    if (argc == 3)
      {
	teste = 0;
	x = 0;
	
        for (x = 0; x < 10; x++)
	  {
            if ((strcmp (argv[1], planetas[x].nome)) == 0)
	      {
                if ((strcmp (argv[2], "Distância_média_ao_Sol")) == 0)
		  {
		    titulo ();
		    printf ("\nDistância média ao sol do planeta %s : %lg km.\n", planetas[x].nome, planetas[x].distancia);
		    teste = 1;
		    fim ();
		  }
                
                if ((strcmp (argv[2], "Massa")) == 0)
		  {
		    titulo ();
		    printf ("\nMassa do planeta %s : %lg kg.\n", planetas[x].nome, planetas[x].massa);
		    teste = 1;
		    fim ();
		  }
		  
                if ((strcmp (argv[2], "Inclinação_orbital")) == 0)
		  {
		    titulo ();
		    printf ("\nInclinação orbital do planeta %s : %lgº.\n", planetas[x].nome, planetas[x].inclinacao);
		    teste = 1;
		    fim ();
		  }
		  
                if ((strcmp (argv[2], "Raio_médio")) == 0)
		  {
		    titulo ();
		    printf ("\nRaio médio do planeta %s : %lg km.\n", planetas[x].nome, planetas[x].raio);
		    teste = 1;
		    fim ();
		  }
		  
                if ((strcmp (argv[2], "Tempo_de_revolução")) == 0)
		  {
		    titulo ();
		    printf ("\nTempo de revolução do planeta %s : %lg dias.\n", planetas[x].nome, planetas[x].trevolucao);
		    teste = 1;
		    fim ();
		  }
		  
                if ((strcmp (argv[2], "Período_de_translação")) == 0)
		  {
		    titulo ();
		    printf ("\nPeríodo de translação do planeta %s : %lg anos.\n", planetas[x].nome, planetas[x].ttranslacao);
		    teste = 1;
		    fim ();
		  }
		  
                if ((strcmp (argv[2], "Número_de_satélites")) == 0)
		  {
		    titulo ();
		    printf ("\nNúmero de satélites do planeta %s : %d.\n", planetas[x].nome, planetas[x].satelites);
		    teste = 1;
		    fim ();
		  }
		  
                if ((strcmp (argv[2], "Anao")) == 0)
		  {
                    if ((strcmp (planetas[x].anao, "Sim")) == 0)
		      {
			titulo ();
			printf ("\nO planeta %s é um planeta anão.\n", planetas[x].nome);
			teste = 1;
			fim ();
		      }
		      
                    if ((strcmp (planetas[x].anao, "Não")) == 0)
		      {
			titulo ();
			printf ("\nO planeta %s não é um planeta anão.\n", planetas[x].nome);
			teste = 1;
			fim ();
		      }
		  }
	      }
	  }

	if (teste == 0)
	  erro ();
      }
    
    return 0;
}

// NOTA: informação disponível em https://solarsystem.nasa.gov/planet-compare/ e noutros links do mesmo site
