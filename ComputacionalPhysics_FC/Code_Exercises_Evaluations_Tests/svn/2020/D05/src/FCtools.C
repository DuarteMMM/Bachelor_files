/******************************************************
 *                Física Computacional                *
 *                    FCtools.C                       *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include <fstream> // ifstream
#include <cstddef>
#include <iostream> // cout
#include <cstdio> // printf
#include <sstream>
#include "FCtools.h"

//#define DEBUG

using namespace std;

// Output: vetor com as linhas do ficheiro
vector<string> FCtools::ReadFile2String (string File_Name)
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  ifstream File (File_Name); // stream class para ler de ficheiros

  string Line = ""; // Onde se vão colocando as linhas lidas

  vector<string> VectorLines; // Vetor com as linhas 

  // Se ficheiro não foi aberto corretamente
  
  if (!File.is_open())
    {
      cout << "\n ERRO: O ficheiro " << File_Name << " não abriu corretamente. Foi-lhe atribuída a matriz identidade 3x3.\n" << endl;
      VectorLines.push_back ("1. 0. 0.");
      VectorLines.push_back ("0. 1. 0.");
      VectorLines.push_back ("0. 0. 1.");
    }

  else
    {
      while (getline (File, Line))
        {
          VectorLines.push_back (Line);
          Line.clear();
        }
      
      File.close();
    }

  return VectorLines;
}

// Output: vector com as linhas da matriz
vector<Vec> FCtools::ReadFile2Vec (string FileName)
{
  vector<string> LineVector = ReadFile2String(FileName);
  int N = LineVector.size();

  vector<Vec> VecVector;

  double *TArray = new double[N];

  stringstream ss;

  for (int i = 0; i < N; i++)
    {
      ss << LineVector[i];

      for (int j = 0; j < N; j++)
        ss >> TArray[j];

      VecVector.push_back(Vec(N, TArray));

      ss.clear();
    }

  delete[] TArray;

  return VecVector;
}

// Output: pointer para array de Vec com as linhas da matriz
Vec *FCtools::ReadFile2Vecp(string FileName)
{
  vector<string> LineVector = ReadFile2String(FileName);
  int N = LineVector.size();

  Vec *VecPointer = new Vec[N];

  double *TArray = new double[N];

  stringstream ss;

  for (int i = 0; i < N; i++)
    {
      ss << LineVector[i];

      for (int j = 0; j < N; j++)
        ss >> TArray[j];

      VecPointer[i].SetEntries(N, TArray);

      ss.clear();
    }

  delete[] TArray;

  return VecPointer;
}
