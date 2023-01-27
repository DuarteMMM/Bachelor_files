/******************************************************
 *                Física Computacional                *
 *                       Vec.C                        *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

#include "Vec.h"
//#include "FCtools.h"

#include <algorithm> //copy,...
#include <stdexcept>
#include <iomanip>
#include <numeric>
#include <cmath>

#include "TString.h"

//#define DEBUG
#define TOLERANCE 1e-6

using namespace std;


//constructors
Vec::Vec() : N(0), entries(new double[0]) {;}


//Vec com n elementos, iguais a zero
Vec::Vec(int n) {
  
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  
  if (n < 0)
    throw invalid_argument(TString::Format("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  
  else {
    
    N = n;

    entries = new double[N];
    for (int i = 0; i < n; i++)
      entries[i] = 0;

  }
}


//Vec com i elementos, iguais a x
Vec::Vec(int i, double x) {

  if (i < 0)
    throw invalid_argument(TString::Format("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  
  else {
    
    N = i;
    
    entries = new double[i];
    /*
      for (int j = 0; j < i; j++)
      entries[j] = 0.;*/
    fill_n (entries, i, x);
  }
}


//Vec com n elementos, dados pelo vetor x
Vec::Vec(int i, double* x){
  
  if (i < 0)
    throw invalid_argument(TString::Format("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  
  else {
    
    if (!x) {
    
      throw std::invalid_argument(TString::Format("[%s] null pointer to array...!\n", __PRETTY_FUNCTION__));
    
    } else {
    
      N = i;
      entries = new double[N];
      copy(x, x+N, entries);
    
    }
    
  }
}


// Copy Constructor
Vec::Vec(const Vec& v) : Vec (v.N, v.entries) {
  /*
    N = v.N;
    entries = new double [N];
    for (int i = 0; i < N; i++)
    entries[i] = v.entries[i];*/
}


//Destructor
Vec::~Vec()
{
  if (entries) delete [] entries;
}


void Vec::SetEntries(int n, const double* arg) {
  if (n < 0)
    throw invalid_argument(TString::Format("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));

  else if (!arg)
    throw invalid_argument(TString::Format("[%s] received null array of elements...!\n", __PRETTY_FUNCTION__));
    
  else {
  
    if (entries != NULL) {

      delete[] entries;

    }
    
    N = n;
    entries = new double[N];
    copy(arg, arg+N, entries);
    /*for (int i = 0; i < N; i++)
      entries[i] = arg[i];*/
    
  }
}



//////////////////////Operators


Vec& Vec::operator=(const Vec& v)
{
  if (&v != this)
    {
      N = v.N;
      if (entries) delete[] entries;
      entries = new double[N];

      /*
	for (int i = 0; i < N; i++)
	entries[i] = v.entries[i];*/

      copy (v.entries, v.entries+N, entries);   
    }

  return *this;
}


// Para fazer sinal positivo do vetor (deixá-lo igual...) 
Vec Vec::operator+() const
{
  return Vec(*this);
}


Vec Vec::operator+(const Vec& v) const
{
  if (N != v.N) {
    throw invalid_argument(TString::Format("[%s] received 2 Vecs of different sizes...!\n", __PRETTY_FUNCTION__));
  } else {


    double* SumA = new double[N];

    for (int i = 0; i < N; i++)
      SumA[i] = entries[i] + v[i];

    Vec SumV(N, SumA);

    delete[] SumA;

    return SumV;
    
  }
}


Vec& Vec::operator+=(const Vec &v)
{
  if (N != v.N)
    throw invalid_argument(TString::Format("[%s] received 2 Vecs of different sizes...!\n", __PRETTY_FUNCTION__));
  
  else
    {
      for (int i = 0; i < N; i++)
	entries[i] += v[i];
      return *this;
    }
}


// Trocar sinal dos elementos do vetor
Vec Vec::operator-() const
{
  Vec Result(N);

  for (int i = 0; i < N; i++)
    Result.entries[i] = -entries[i];

  return Result;
}

Vec Vec::operator-(const Vec& Obj) const
{
  if (N != Obj.N)
    {
      throw invalid_argument(TString::Format("[%s] received 2 Vecs of different sizes...!\n", __PRETTY_FUNCTION__));
      
    } else {

    double *DifA = new double[N];
    
    for (int i = 0; i < N; i++)
      DifA[i] = entries[i] - Obj[i];

    Vec DifV(N, DifA);

    delete[] DifA;

    return DifV;
    
  }
}

Vec& Vec::operator-=(const Vec& Obj)
{
  if (N != Obj.N)
    throw invalid_argument(TString::Format("[%s] received 2 Vecs of different sizes...!\n", __PRETTY_FUNCTION__));

  else
    {
      for (int i = 0; i < N; i++)
	entries[i] -= Obj[i];
    }

  return *this;
}

double& Vec::operator[](int i)
{
  if (i < 0 || i >= N)
    {
      throw invalid_argument(TString::Format("[%s] received invalid position...!\n", __PRETTY_FUNCTION__));
    }

  return entries[i];
}

double Vec::operator[](int i) const
{
  if (i < 0 || i >= N)
    {
      throw invalid_argument(TString::Format("[%s] received invalid position...!\n", __PRETTY_FUNCTION__));
    }

  return entries[i];
}

Vec Vec::operator*(double x) const
{
  /*if ((abs(Scalar)-1) < TOLERANCE)
    return *this;*/
  
  double *DifA = new double[N];

  for (int i = 0; i < N; i++)
    DifA[i] = x * entries[i];

  Vec DifV (N, DifA);

  delete[] DifA;

  return DifV;
}

Vec Vec::operator/(double x) const
{
  /*if ((abs(Scalar)-1) < TOLERANCE)
    return *this;*/
  
  double *DifA = new double[N];

  for (int i = 0; i < N; i++)
    DifA[i] = entries[i] / x;

  Vec DifV (N, DifA);

  delete[] DifA;

  return DifV;
}



Vec Vec::operator*=(double x) {
  /*if ((abs(x)-1) < TOLERANCE)
    return *this;*/
  
  for (int i = 0; i < N; ++i) {
    entries[i] *= x;
  }
  
  return *this;
}


Vec Vec::operator/=(double x) {
  /*if ((abs(x)-1) < TOLERANCE)
    return *this;*/
  
  for (int i = 0; i < N; ++i) {
    entries[i] /= x;
  }
  
  return *this;
}



/////////////////////////////////////////friends


Vec operator*(double x, const Vec &Vector)
{
  /*if ((abs(x)-1) < TOLERANCE)
    return Vector;*/
  
  int N = Vector.N;
  double *a = new double[N];

  for (int i = 0; i < N; i++)
    a[i] = x * Vector.entries[i];

  Vec v(N, a);

  delete[] a;

  return v;
}

ostream& operator<< (ostream& s, const Vec& v) {
  s << "[";
  for (int i = 0; i < v.N; ++i) {
    s << fixed << setprecision(6) << v.entries[i];
    if (i < v.N-1) s << ", ";
  }
  s << "]";
  
  return s;
}


///////////////////////////////// Outros métodos


int Vec::size() const
{
  return N;
}


// Produto interno
double Vec::dot(const Vec &v) const
{
  if (N != v.N)
    {
      throw invalid_argument(TString::Format("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));
    }
  
  /*
    double produto = 0.;

    for (int i = 0; i < N; i++)
    produto += entries[i] * v[i];

    return produto;*/
  
  return inner_product(entries, entries+N, v.entries, 0.);
}


/*void Vec::Print() const
  {
  cout << "|";

  for (int i = 0; i < N; i++)
  printf(" %4.3lf ", entries[i]);

  cout << "|" << endl;
  }*/


double Vec::sumAbs() {
  
  double valor =  accumulate (entries, entries+N, 0.0, [](double accum, double x){return accum+fabs(x);});
  
  return valor;
}


// Trocar 2 elementos de ordem
void Vec::swap(int n, int m)
{
  if ((n < 0) || (m < 0) || (n >= N) || (m >= N))
    throw invalid_argument(TString::Format("[%s] indices out of range...(N=%d max index=%d)!\n", __PRETTY_FUNCTION__, N, std::max(n,m)));
  
  else
    {
      double x = entries[n];
      entries[n] = entries[m];
      entries[m] = x;
    }
}

// Valor máximo em valor absoluto
double Vec::maxAbs() {
  return *max_element(entries, entries+N, [](double x1, double x2){ return fabs(x1) < fabs(x2);}); // este método retorna o iterador para elemento máximo (sendo um iterador, temos que desreferenciá-lo para ter acesso ao valor do elemento… daí o uso do *)
}


double Vec::max() const {

  auto it = max_element(entries, entries + N);

  return *it;

}


double Vec::min() const {

  auto it = min_element(entries, entries + N);

  return *it;

}


void Vec::AddEntry(double x) {

  int new_N = N+1;
  double* updated = new double[new_N];

  if (entries) {
    
    copy(entries, entries+N, updated);
    delete[] entries;
    entries = new double[new_N];
    
  }
  
  updated[N] = x;

  delete [] entries;
  
  N = new_N;
  entries = new double [N];
  copy(updated, updated+N, entries);
  
  delete[] updated;
}

double Vec::RemoveLastEntry() {

  double lastentry = entries[N-1];
  N--;

  return lastentry;
}

double* Vec::GetEntries()
{
  return entries;
}
