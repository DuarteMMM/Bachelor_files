#ifndef __Func1D__
#define __Func1D__

#include "TF1.h"

class Func1D{

 public:

  Func1D(const TF1* fp=nullptr); // constructor1
  Func1D(const TF1&); // constructor2
  Func1D(const Func1D&); // copy constructor
  virtual ~Func1D(); // destructor (virtual de forma a que as classes derivadas também chamem o destrutor de Func1D, não apenas os deles, de forma a não ficarem coisas por destruir)

  // drawing
  void Draw();

  // evaluate
  double Eval(double) const;
  
  // change the function
  void SetFunc(TF1 *);
  
  // return function
  TF1 *GetFunc() const;
  
  // return value (positive or negative) of largest value (in absolute value) of function
  double GetMaxValue();
  
	  
  // change title (useful for high order derivatives)
  void SetTitle (const char*);
  
 protected:

  void Settings();
  
  TF1* f;
  
};

#endif
