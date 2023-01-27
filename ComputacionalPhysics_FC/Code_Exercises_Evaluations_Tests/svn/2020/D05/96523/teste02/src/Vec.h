#ifndef __Vec__
#define __Vec__


#include <iostream> // ostream


using namespace std;


class Vec {
  
public:

  // Constructors
  Vec ();
  Vec (int);
  Vec (int, double); // (int) elements all equal to (double);
  Vec (int, double*);
  Vec (const Vec&); // Copy constructor

  // Destructor
  ~Vec();

  // Redefinir objeto Vec de n elementos com o conteúdo de array
  void SetEntries (int, const double*);

  //Operators
  Vec&    operator=  (const Vec &)          ;
  Vec     operator+  ()               const ;
  Vec     operator+  (const Vec &)    const ;
  Vec&    operator+= (const Vec &)          ;
  Vec     operator-  ()               const ;
  Vec     operator-  (const Vec &)    const ;
  Vec&    operator-= (const Vec &)          ;
  double& operator[] (int)                  ;
  double  operator[] (int)            const ;
  //Vec     operator*  (const Vec &)    const ;
  Vec     operator*  (double) const ;
  Vec     operator/ (double) const;
  Vec     operator*=(double);
  Vec     operator/=(double);

  // friend methods
  friend Vec operator* (double, const Vec&); // Este método é para se poder usar o cálculo escalar*vetor
  
  friend ostream& operator<<(ostream&, const Vec&); // Mostra no ecrã valores do vetor com precisão 6 e parêntesis retos

  // Outros métodos
  int size() const; // Dimensão do vetor
  double dot (const Vec&) const; // Produto interno com outro vetor
  double max() const;
  double min() const;
  double sumAbs(); // Soma de todos os valores absolutos
  void swap(int, int);            // Trocar 2 elementos de ordem
  double maxAbs(); // maximal abs (value) of Vec
  void AddEntry(double);
  
  double RemoveLastEntry(); //removes the last entry and returns a copy of it
  double* GetEntries();
  
private:
  int N; //number of elements
  double *entries; // pointer to array of doubles
};


#endif
