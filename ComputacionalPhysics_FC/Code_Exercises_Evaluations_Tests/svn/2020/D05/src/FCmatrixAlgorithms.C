#include "FCmatrixAlgorithms.h"

#include <numeric> // std::iota

#include "TString.h"


#define TOLERANCE 1.e-300
//#define DEBUG


using namespace std;


// Gauss Elimination
void FCmatrixAlgorithms::GaussElimination(FCmatrixFull &matriz_A, int flag, int if_augmented)
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  const int n = matriz_A.Get_nRows();
  const int n1 = n - 1;
  const int m = matriz_A.Get_nCols(); //se a matriz for aumentada, o vetor extra conta como coluna
  const int m_notaugmented = m - if_augmented; // Se a matriz for aumentada, fica guardado o número de colunas da matriz não aumentada; se a matriz não for aumentada, é igual a m
  
  
  // Sem pivotagem
  if (flag == 0) {
    
    int i=0, j=0; // Linha e coluna, respetivamente
  
    while (i < n1 && j < m_notaugmented) {

      //caso o elemento pivot seja 0 tem que haver troca de linhas
      if (abs(matriz_A[i][j]) < TOLERANCE){
	for (int k=(i+1); k < n; k++){
	  //procuramos uma linha tal que o novo pivot não seja 0
	  if (abs(matriz_A[k][j]) > TOLERANCE){
	    matriz_A.swapRows (i, k);
	    //k = n+1; // Para parar o ciclo
	    break;
	  }
	}
	// caso o pivot continue a 0, ou seja, se todos os elementos da coluna forem zero, avançamos para a coluna seguin
	if (abs(matriz_A[i][j]) < TOLERANCE)
	  j++;

      }

      else if (abs(matriz_A[i][j]) > TOLERANCE) {

	Vec pivot = matriz_A[i];
	
	for (int l = (i+1); l < n; ++l) {
	  if (abs(pivot[j]) > TOLERANCE) {
	    
	    double coef = (-1.)*matriz_A[l][j] / pivot[j];
	    
	    //matriz_A[l] += matriz_A[i]*coef;
	    for (int iterador_colunas = j; iterador_colunas < m; iterador_colunas++) {

		matriz_A[l][iterador_colunas] += coef * pivot[iterador_colunas];
	    
	    }
	  
	  }
	}
	//estamos dentro do "else if"
	i++;
	j++;
      }
      
    }
  }

  // Com pivotagem
  if (flag == 1)
    {

      int pivot_line = 0; //índice da linha pivot
      Vec pivot_vec; //vai receber a linha pivot em cada iteração
      int current_col = 0;
      double Gauss_coef = 0.;
      int max_col; 

      while (pivot_line < n1 && current_col < m_notaugmented) {

	//vamos buscar o índice da linha cujo valor na current_col será o melhor pivot (quociente entre ele e o máximo da linha é máximo, tudo em módulo)
	max_col = matriz_A.GetColMax(pivot_line, current_col);

	//fazemos a troca de modo a ter o melhor pivot possível
	if (max_col != pivot_line) {

	  matriz_A.swapRows(pivot_line, max_col);

	}

	// Feita já a troca, se for zero o elemento então a coluna é toda zero
	if (abs(matriz_A[pivot_line][current_col]) < TOLERANCE) {
	  
	  //printf ("[%s]: a matriz é singular ou mal condicionada...\n", __PRETTY_FUNCTION__);
	  
	  current_col++;
	  continue; // Ou seja, passamos para a próxima iteração do loop sem fazer eliminação

	}

	pivot_vec = matriz_A[pivot_line];
    
	// Eliminação das linhas (a seguir à pivot)
	for (int i = pivot_line + 1; i < n; i++) {
      
	  if (abs(matriz_A[i][current_col]) > TOLERANCE) // Só eliminar se o primeiro elemento da linha i não for zero...
	    {

	      // Coeficiente para multiplicar pela linha pivot e subtrair à atual
	      Gauss_coef = matriz_A[i][current_col] / pivot_vec[current_col];

	      //subtração feita sem reaproveitar os operadores de matrizes para poupar tempo (os elementos que já estão a zero não são multiplicados nem subtraídos), m = nº colunas
	      for (int j = current_col; j < m; j++) {

		matriz_A[i][j] -= Gauss_coef * pivot_vec[j];
		
	      }

	      //matriz_A[i] -= Gauss_coef * matriz_A[pivot_line];

	    }
	  // Para garantir que fica zero no início da linha, não algo muito próximo

	  matriz_A[i][current_col] = 0.;

	}

	// Avançar na diagonal
	pivot_line++;
	current_col++;
      }
    }
}


// GaussJordan Elimination
void FCmatrixAlgorithms::GaussJordan(FCmatrixFull& matriz_A, FCmatrixFull& I, int flag)
{
  // Parte inicial do algoritmo análoga a GaussElimination
  const int n = matriz_A.Get_nRows();
  const int n1 = n - 1;

  if (flag == 0) {

    int i=0, j=0;
  
    while (i < n1 && j < n) {

      if (abs(matriz_A[i][j]) < TOLERANCE){
	for (int k=(i+1); k < n; k++){
	  if (abs(matriz_A[k][j]) > TOLERANCE){
	    matriz_A.swapRows (i, k);
	    I.swapRows (i, k);
	    k = n+1; 
	  }
	}

	if (abs(matriz_A[i][j]) < TOLERANCE)
	  j++;
      }

      else if (abs(matriz_A[i][j]) > TOLERANCE) {
	for (int l = (i+1); l < n; ++l) {
	  if (abs(matriz_A[l][j]) > TOLERANCE )
	    {
	      double coef = (-1.)*matriz_A[l][j] / matriz_A[i][j];
	      matriz_A[l] += matriz_A[i]*coef;
	      I[l] += I[i]*coef;
	    }
	}
	i++;
	j++;
      }
    }
  }


  if (flag == 1)
    {
      int pivot_line = 0;
      int current_col = 0;
      double Gauss_coef = 0.;
      int max_col;

      while (pivot_line < n1 && current_col < n) {
    
	max_col = matriz_A.GetColMax(pivot_line, current_col);
	
	if (max_col != pivot_line){
	  matriz_A.swapRows(pivot_line, max_col);
	  I.swapRows (pivot_line, max_col);
	}
	
	if (abs(matriz_A[pivot_line][current_col]) < TOLERANCE) {
      
	  current_col++;
	  continue;

	}
    
	for (int i = pivot_line + 1; i < n; i++) {
      
	  if (abs(matriz_A[i][current_col]) > TOLERANCE)
	    {
	      Gauss_coef = matriz_A[i][current_col] / matriz_A[pivot_line][current_col];
	      matriz_A[i] -= Gauss_coef * matriz_A[pivot_line];
	      I[i] -= Gauss_coef * I[pivot_line];

	    }
	  matriz_A[i][current_col] = 0.;
	}

	pivot_line++;
	current_col++;
      }
    }

  int current_line = n-2;
  int cont_col = n-1;
  int cont_line = n-2;

  // Obter matriz-diagonal a partir da matriz_A resolvida (Gauss)
  while (cont_col >= 1)
    {
      while (cont_line >= 0)
	{
	  if (abs(matriz_A[cont_line][cont_col]) > TOLERANCE)
	    {
	      double coef = (-1.)*matriz_A[cont_line][cont_col] / matriz_A[cont_col][cont_col];
	      matriz_A[cont_line] += matriz_A[cont_col]*coef;
	      I[cont_line] += I[cont_col]*coef;
	    }
	  cont_line--;
	}
      cont_col--;
      current_line--;
      cont_line = current_line;
    }

  // Transformar matriz_A em matriz identidade
  for (int cont_diag=0; cont_diag < n; cont_diag++) {
    if (matriz_A[cont_diag][cont_diag] != 1.)
      {
	I[cont_diag] = I[cont_diag] / matriz_A[cont_diag][cont_diag];
	matriz_A[cont_diag] = matriz_A[cont_diag] / matriz_A[cont_diag][cont_diag];
      }
  }
}



// LU Decomposition
void FCmatrixAlgorithms::LUdecomposition (FCmatrixFull &matriz_A) {
  
  int n = matriz_A.Get_nRows();
  int n1 = n - 1;
  int m = matriz_A.Get_nCols();
  int i=0, j=0; // Linha e coluna, respetivamente

  if (n != m)
    throw invalid_argument(TString::Format("[%s]: the LU decomposition only applies to square matrices\n", __PRETTY_FUNCTION__));

  FCmatrixFull LU (matriz_A);
  
  while (i < n1 && j < m) {

    if (abs(LU[i][j]) < TOLERANCE){
      for (int k=(i+1); k < n; k++){
	if (abs(LU[k][j]) > TOLERANCE)
	  throw invalid_argument(TString::Format("[%s]: não pode ocorrer troca de linhas na decomposição LU\n", __PRETTY_FUNCTION__));
      }
      // Depois de eventual troca
      if (abs(LU[i][j]) < TOLERANCE)
        throw invalid_argument(TString::Format("[%s]: a matriz não tem solução determinada\n", __PRETTY_FUNCTION__)); // Porque é quadrada e tem uma coluna só com zeros
    }

    else if (abs(LU[i][j]) > TOLERANCE) {
      for (int l = (i+1); l < n; ++l) {
	double coef = LU[l][j] / LU[i][j];
	for (int v = j+1; v < m; ++v) {
	  LU[l][v] -= (LU[i][v] * coef);
	}
	LU[l][j] = coef;
      }
      i++;
      j++;
    }
  }

  matriz_A = LU;
}
