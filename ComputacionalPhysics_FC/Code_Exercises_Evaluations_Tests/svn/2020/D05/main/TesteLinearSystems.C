// TESTE DE CLASSES

#include "FCtools.h"
#include "Vec.h"
#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "FCmatrixAlgorithms.h"
#include "EqSolver.h"
#include <string> // classe string
#include <vector> // Para vetores STL

using namespace std;

int main()
{
  // ====================== Vec ======================
  cout << "\n===== Vec =====\n" << endl;

  // Constructor 1
  cout << "---> Constructor 1, vetor b" << endl;
  Vec b; // Empty Vec
  cout << b << endl;

  // Constructor 2
  cout << "\n---> Constructor 2, vetor c" << endl;
  Vec c(10); // Vetor com 10 elementos iguais a zero
  cout << c << endl;
  
  // Constructor 3
  cout << "\n---> Constructor 3, vetor d" << endl;
  Vec d(10, 5.);
  cout << d << endl;
  
  // Constructor 4
  cout << "\n---> Constructor 4, vetor e" << endl;
  double x[]={1.2, 3.0, 5.4, 5.2, 1.0};
  Vec e(5, x);
  cout << e << endl;

  // Copy constructor
  cout << "\n---> Copy constructor, vetor g" << endl;
  Vec g(e);
  cout << g << endl;
 
  // Set Entries
  cout << "\n---> Set Entries, vetor d" << endl;
  d.SetEntries (5, x);
  cout << d << endl;
 
  // Operador =
  cout << "\n---> Operador =, vetor h=d" << endl;
  Vec h = d;
  cout << h << endl;

  // Operador + (sinal positivo)
  cout << "\n---> Operador + (sinal), vetor l=+d" << endl;
  Vec l = +d;
  cout << l << endl;
  
  // Operador + (soma)
  cout << "\n---> Operador + (soma), vetor i=d+h" << endl;
  Vec i = d+h;
  cout << i << endl;

  // Operador +=
  cout << "\n---> Operador +=, vetor i=i+d" << endl;
  i += d;
  cout << i << endl;

  // Operador - (sinal)
  cout << "\n---> Operador - (sinal), vetor k=-i" << endl;
  Vec k = -i;
  cout << k << endl;
  
  // Operador - (subtração)
  cout << "\n---> Operador - (subtração), vetor j=i-d" << endl;
  Vec j = i-d;
  cout << j << endl;

  // Operador -=
  cout << "\n---> Operador -=, vetor j=j-i" << endl;
  j -= i;
  cout << j << endl;

  // Operador [] é acedido ao longo do programa, nas várias funções
  // Operador [] const é acedido agora, por exemplo:
  cout << "\n---> Operador [] const, j[0]" << endl;
  cout << j[0] << endl;

  // Operador * entre vetor e escalar
  cout << "\n---> Operador * entre vetor e escalar, n = i*0.5" << endl;
  Vec n = i*0.5;
  cout << n << endl;

  // Operador *= (vetor=vetor*escalar)
  cout << "\n---> Operador *= aplicado a um vetor, n*=0.5" << endl;
  n *= 0.5;
  cout << n << endl;

  // Operador ostream
  cout << "\n---> Operador <<, vetor n" << endl;
  cout << n << endl;

  // Size
  cout << "\n---> Operador size, do vetor n" << endl;
  cout << n.size() << endl;

  // Produto interno
  cout << "\n---> Produto interno entre i e n" << endl;
  cout << i.dot(n) << endl;

  // Somar todos os valores absolutos
   cout << "\n---> Soma de todos os valores absolutos, vetor n" << endl;
   cout << n.sumAbs() << endl;
   
  // Trocar dois elementos
  cout << "\n---> Trocar elementos de ordem 0 e 1 de n" << endl;
  cout << "Original: ";
  cout << n << endl;
  n.swap (0, 1);
  cout << "Novo: ";
  cout << n << endl;

  // Obter máximo valor absoluto do vetor
  cout << "\n---> Máximo elemento em módulo, matriz n" << endl;
  cout << n.maxAbs() << endl;
  
  // ====================== FCtools ======================
  cout << "\n===== FCtools =====" << endl;
  FCtools f; // Criar objeto FCtools para usar os seus métodos
  
  cout << "\n---> ReadFile2String: coloca linhas do ficheiro num vetor de strings" << endl;
  vector<string> a = f.ReadFile2String ("./main/Teste.txt"); // Tive de colocar a pasta onde está o ficheiro... Dá sem?
  cout << a[0] << endl << a[1] << endl << a[2] << endl; // deu bem
  a.clear();

  cout << "\n---> ReadFile2Vec: coloca linhas do ficheiro num vetor de Vecs" << endl;
  vector<Vec> vetor_Vecs = f.ReadFile2Vec ("./main/Teste.txt");
  for (int i=0; i<3; i++)
    {
      cout << vetor_Vecs[i] << endl;
    }

  cout << "\n---> ReadFile2Vecp: coloca linhas do ficheiro num ponteiro Vec" << endl;
  Vec* VecPointer = f.ReadFile2Vecp ("./main/Teste.txt");
  for (int l=0; l<3; l++)
    {
      cout << VecPointer[l] << endl;
    }

  delete []VecPointer; // Aqui apaga-se, porque não é apenas Vec (nesse caso, é chamado o destrutor da classe Vec), mas sim um Vec*

  // ====================== FCmatrixFull ======================
  
  cout << "\n===== FCmatrixFull =====" << endl;

  // Construtor 1
  cout << "\n---> Construtor 1: matrizA" << endl;
  FCmatrixFull matrizA;
  cout << matrizA << endl;

  // Construtor 2
  cout << "\n---> Construtor 2: matrizB" << endl;
  
  double **vec_matrizB = new double* [3];
  vec_matrizB[0] = new double[2] {1.0, 2.0};
  vec_matrizB[1] = new double[2] {3.0, 4.0};
  vec_matrizB[2] = new double[2] {5.0, 6.0};
  FCmatrixFull matrizB(vec_matrizB, 3, 2);
  cout << matrizB << endl;

  delete vec_matrizB[0];
  delete vec_matrizB[1];
  delete vec_matrizB[2];
  delete []vec_matrizB;

  // Construtor 3
  cout << "\n---> Construtor 3: matrizC" << endl;
  double vec_matrizC[] = {2., 4., 6., 8., 10., 12.};
  FCmatrixFull matrizC (vec_matrizC, 3, 2);
  cout << matrizC << endl;

  // Construtor 4
  cout << "\n---> Construtor 4: matrizD" << endl;
  FCmatrixFull matrizD (vetor_Vecs); // vetor_Vecs já feito acima, para FCTools
  cout << matrizD << endl;

  // Copy constructor
  cout << "\n---> Copy constructor, matrizE = matrizD" << endl;
  FCmatrixFull matrizE (matrizD);
  cout << matrizE << endl;

  // Operator []
  cout << "\n---> Operador [], matrizE[1]" << endl;
  Vec linha1_matrizE = matrizE[1];
  cout << linha1_matrizE << endl;

  // Copy assignment
  cout << "\n---> Copy assignment, matrizF = matrizE" << endl;
  FCmatrixFull matrizF = matrizE;
  cout << matrizF << endl;

  // Operador +
  cout << "\n---> Operador +, matrizG = matrizE + matrizF" << endl;
  FCmatrixFull matrizG = matrizE + matrizF;
  cout << matrizG << endl;

  // Operador -
  cout << "\n---> Operador -, matrizH = matrizG - matrizF" << endl;
  FCmatrixFull matrizH = matrizG - matrizF;
  cout << matrizH << endl;

  // Operador * (matrizes)
  cout << "\n---> Operador *, matrizG = matrizH*matrizF" << endl;
  matrizG = matrizH*matrizF;
  cout << matrizG << endl;

  // Operador * (matriz por escalar)
  cout << "\n---> Operador *, matrizG = matrizG*0.1" << endl;
  matrizG = matrizG*0.1;
  cout << matrizG << endl;

  // Operador * (matriz por Vec: resultado é Vec)
  cout << "\n---> Operador*, Vec z = matrizG*(2., 2., 2.)" << endl;
  Vec y(3, 2.); // Construtor 3 da classe Vec
  Vec z = matrizG*y;
  cout << z << endl;

  // Número de linhas
  cout << "\n---> Get_nRows() (da matrizG)" << endl;
  cout << matrizG.Get_nRows() << endl;

  // Número de colunas
  cout << "\n---> Get_nCols() (da matrizG)" << endl;
  cout << matrizG.Get_nCols() << endl;
  
  // Obter linha da matriz (tal como no operador []...)
  cout << "\n---> GetRow(int i), linha i=1 da matrizG" << endl;
  Vec vec_linha1_matrizG = matrizG.GetRow (1);
  cout << vec_linha1_matrizG << endl;

  // Obter coluna da matriz
  cout << "\n---> GetCol(int j), coluna j=0 da matrizG" << endl;
  Vec vec_coluna0_matrizG = matrizG.GetCol (0);
  cout << vec_coluna0_matrizG << endl;

  // Calcular determinante
  cout << "\n---> Determinant()" << endl; // Vou calcular para várias matrizes

  vector<Vec> Vetor_vecs_teste1 = f.ReadFile2Vec ("./main/MatrizTeste1.txt");
  FCmatrixFull Matriz_teste1 (Vetor_vecs_teste1);
  cout << "\nMatriz 1x1" << endl;
  cout << Matriz_teste1 << endl;
  cout << "Determinante: " << Matriz_teste1.GetDeterminant() << endl;

  vector<Vec> Vetor_vecs_teste2 = f.ReadFile2Vec ("./main/MatrizTeste2.txt");
  FCmatrixFull Matriz_teste2 (Vetor_vecs_teste2);
  cout << "\nMatriz 2x2" << endl;
  cout << Matriz_teste2 << endl;
  cout << "Determinante: " << Matriz_teste2.GetDeterminant() << endl;

  vector<Vec> Vetor_vecs_teste3 = f.ReadFile2Vec ("./main/MatrizTeste3.txt");
  FCmatrixFull Matriz_teste3 (Vetor_vecs_teste3);
  cout << "\nMatriz 3x3" << endl;
  cout << Matriz_teste3 << endl;
  cout << "Determinante: " << Matriz_teste3.GetDeterminant() << endl;

  vector<Vec> Vetor_vecs_teste4 = f.ReadFile2Vec ("./main/MatrizTeste4.txt");
  FCmatrixFull Matriz_teste4 (Vetor_vecs_teste4);
  cout << "\nMatriz 4x4" << endl;
  cout << Matriz_teste4 << endl;
  cout << "Determinante: " << Matriz_teste4.GetDeterminant() << endl;

  vector<Vec> Vetor_vecs_teste5 = f.ReadFile2Vec ("./main/MatrizTeste5.txt");
  FCmatrixFull Matriz_teste5 (Vetor_vecs_teste5);
  cout << "\nMatriz 5x5" << endl;
  cout << Matriz_teste5 << endl;
  cout << "Determinante: " << Matriz_teste5.GetDeterminant() << endl;

  cout << "Soma em linhas 0 a 5, em módulos: " << Matriz_teste5.GetSumLine (0) << "   " <<  Matriz_teste5.GetSumLine (1) << "   " <<  Matriz_teste5.GetSumLine (2) << "   " <<  Matriz_teste5.GetSumLine (3) << "   " <<  Matriz_teste5.GetSumLine (4) << endl;

  cout << "\nNorma infinito da matriz: " << Matriz_teste5.GetNormaInfMatriz() << endl;

  cout << "\nNorma 2 da matriz: " << Matriz_teste5.GetNorma2Matriz() << endl;

  // Verifiquei online os determinantes maiores: estão certos!

  // GetRowMax (retorna índice do maior valor da linha, em módulo)
  cout << "\n---> GetRowMax, Matriz_teste5[1]" << endl;
  cout << Matriz_teste5.GetRowMax (1) << endl;

  // GetColMax
  cout << "\n---> GetColMax, Matriz_teste5 coluna j=1, a partir da linha i=1" << endl;
  cout << Matriz_teste5.GetColMax (1, 1) << endl;

  // swapRows
  cout << "\n---> swapRows, Matriz_teste5 colunas j=2 e j=3" << endl;
  Matriz_teste5.swapRows (2, 3);
  cout << Matriz_teste5 << endl;

  // Print: tem sido usado ao longo do programa

  // ostream
  cout << "\n---> ostream, Matriz_teste5" << endl;
  cout << Matriz_teste5 << endl;

  // ====================== EqSolver ======================

  cout << "\n=================== EqSolver\n";

  // Gauss e Doolittle
  
  cout << "\n--------> Decomposição LU e eliminação de Gauss" << endl;
  double* b1_array = new double[3];
  b1_array[0] = 0.;
  b1_array[1] = 1.5;
  b1_array[2] = 1.;

  Vec b1 (3, b1_array);

  FCmatrixFull Matriz_teste3_copia (Matriz_teste3);
  
  Matriz_teste3.Augment (b1);
  
  EqSolver S1 (Matriz_teste3);
  EqSolver S2 (Matriz_teste3);

  //FCmatrixAlgorithms::GaussElimination (Matriz_teste3, 0, 1);
  //cout << Matriz_teste3 << endl;
  
  Vec Resultado_LU, Resultado_Gauss;
  Resultado_Gauss = S2.GaussEliminationSolver(1); // 1 é com pivotagem
  Resultado_LU = S1.LUdecompositionSolver();
  
  cout << "\nMatriz inicial:\n" << Matriz_teste3 << endl << "\nVetor inicial: " << b1 << endl;
  
  cout << "\nMatriz depois de eliminação de Gauss, com o vetor b alterado:" << endl;
  S2.ShowMatrix();
  FCmatrixFull nova_Gauss = S2.GetMatrix();
  Vec vetor_b_Gauss = S2.Getb();
  cout << "\nVetor dos b alterado:" << vetor_b_Gauss << endl;
  Vec vetor_sols_Gauss = nova_Gauss.RemoveLastCol();
  cout << "\nVetor dos índices:" << vetor_sols_Gauss << endl;

  cout << "\nMatriz depois da decomposição LU, com a coluna dos índices no final:" << endl;
  S1.ShowMatrix();
  FCmatrixFull nova_LU = S1.GetMatrix();
  Vec vetor_b_LU = S1.Getb();
  cout << "\nVetor dos b (não se altera):" << vetor_b_LU << endl;

  
  cout << "\nCom eliminação de Gauss, o resultado é:\n" << Resultado_Gauss << endl << endl;
  cout << "\nCom decomposição LU, o resultado é:\n" << Resultado_LU << endl;

  // Jacobi method
  
  // Neste caso, não há convergência, porque a matriz não é dominante diagonalmente
  /*
  EqSolver SJ (Matriz_teste3_copia, b1);
  double guessJ[]={0., 0. , 0.};
  Vec initial_guessJ (3, guessJ);
  int maxJ = 100000; // Número máximo de iterações
  Vec solutionJ = SJ.JacobiIterator (initial_guessJ, maxJ, 1.e-5);
  cout << "\nVetor das soluções por Jacobi:" << solutionJ << endl;
  */

  cout << "\nJACOBI:" << endl;
  double vec_matrizJacobi[] = {5., 1., 1., 1., 5., 1., 1., 1., 5.};
  FCmatrixFull matrizJacobi (vec_matrizJacobi, 3, 3);
  cout << "Matriz:\n" << matrizJacobi << endl;
  cout << "Vetor dos b: " << b1 << endl;
  EqSolver S3 (matrizJacobi, b1);
  double guess_Jacobi[]={1000.0, 500., -10.0};
  Vec initial_guess_Jacobi (3, guess_Jacobi);
  cout << "Initial guess da solução:" << initial_guess_Jacobi << endl;
  int maxJacobi = 100000; // Número máximo de iterações
  Vec solution_Jacobi = S3.JacobiIterator (initial_guess_Jacobi, maxJacobi, 1.e-5, 1); // Pus aqui 1, que significará com Weighting, mas não faz diferença neste caso, pois não há iterações suficientes
  cout << "\nVetor das soluções por Jacobi do sistema: " << solution_Jacobi << endl;
  cout << "Número de iterações necessárias: " << maxJacobi << endl;

  cout << "\nGAUSS-SEIDEL (mesmo sistema):" << endl;
  maxJacobi = 100000;
  Vec solution_GS = S3.GaussSeidelIterator (initial_guess_Jacobi, maxJacobi, 1.e-5);
  cout << "Vetor das soluções por Gauss-Seidel do sistema: " << solution_GS << endl;
  cout << "Número de iterações necessárias: " << maxJacobi << endl;


  delete [] b1_array;

  cout << endl;
  
  return 0;
}
