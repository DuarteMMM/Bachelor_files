/******************************************************
 *                Física Computacional                *
 *                    Exercício 33                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/
#include "TH1F.h"
#include "stdio.h"

void Exercicio33 () {
  printf ("\n-=-=-=- Exercício 32 -=-=-=-\n\n");
  
  // Alínea a

  TH1F a[2];
  printf ("A alínea a) foi concretizada com sucesso.\n");
  
  // Alínea b

  TH1F b[2] = {TH1F("Nome1", "Titulo1", 10, 0.5, 10.5), TH1F("Nome2", "Titulo2", 10, 0.5, 10.5)};
  printf ("A alínea b) foi concretizada com sucesso.\n");

  // Alínea c

  float y[] = {0.5, 1.0, 1.5, 2.0, 4.5};
  TH1F c[2] = {TH1F("Nome3", "Titulo3", 4, y), TH1F("Nome4", "Titutlo4", 4, y)}; // Atenção! São 4 canais, não 5! (canal de 0.5 a 1.0, de 1.0 a 1.5, etc.)
  printf ("A alínea c) foi concretizada com sucesso.\n");

  // Alínea d

  TH1F d[2];
  d[0].SetBins(10, 0.5, 10.5);
  d[1].SetBins(10, 0.5, 10.5);
  printf ("A alínea d) foi concretizada com sucesso.\n");

  // Alínea e

  TH1F *e[2];
  e[0] = &d[0];
  e[1] = &d[1];
  printf ("A alínea e) foi concretizada com sucesso.\n\n");
  // Ou:
  //TH1F *e[2];
  //e[0] = new TH1F("Nome5", "Titulo5", 10, 0.5, 10.5);
  //e[1] = new TH1F("Nome6", "Titulo6", 10, 0.5, 10.5);

  // Alínea f
  // Não chamei à macro mHisto.C, mas sim Exercicio32.C
}
