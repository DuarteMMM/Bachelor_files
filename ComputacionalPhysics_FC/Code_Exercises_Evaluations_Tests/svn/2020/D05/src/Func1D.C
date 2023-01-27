#include "Func1D.h"

#include "TF1.h"
#include "TH1.h" // Axis names
#include "TCanvas.h"
#include "TApplication.h"

#include <stdexcept> // throw invalid_argument
#include "TString.h" // Format

/////////////////// constructors, destructor

// constructor 1
Func1D::Func1D(const TF1* fp) : f(nullptr) {
  if (fp) {
    f = new TF1(*fp);
    Settings();
  }
}

// constructor 2
Func1D::Func1D(const TF1& fp) : Func1D(&fp) {};

// copy constructor
Func1D::Func1D(const Func1D& og) {f = new TF1(*(og.GetFunc()));};

// destructor
Func1D::~Func1D() {
  if (f) delete f;
}

/////////////////// methods

void Func1D::Settings() {
  f->SetNpx(1000);
  f->SetLineColor(38);
  f->SetLineWidth(4);
  f->GetHistogram()->GetXaxis()->SetTitle("x");
  f->GetHistogram()->GetYaxis()->SetTitle("y");
}

double Func1D::Eval(double xval) const {
  
  double TOLERANCE = 1.e-10; // Importante: Tive de colocar isto devido ao IntegrateTrapezoidal, que não estava a permitir calcular valores no limite do intervlo (em f->GetXmax())...
  
  // Testar se o valor x está no domínio
  if (xval < f->GetXmin()-TOLERANCE || xval > f->GetXmax()+TOLERANCE)
    {
      throw std::invalid_argument(TString::Format("[%s] number was not in range of function!\n", __PRETTY_FUNCTION__));
    }
  
  return f->Eval(xval);
}

void Func1D::Draw(){
  TApplication A("A", 0, 0);
  TCanvas c("c", "Func1D canvas", 0, 0, 1000, 800);
  f->Draw();
  c.Update();
  A.Run();
}

void Func1D::SetFunc(TF1 *fp)
{
  if (f)
    delete(f);

  f = new TF1(*fp);
  Settings();
}

TF1* Func1D::GetFunc() const
{
  return f;
}

double Func1D::GetMaxValue() {
  if (abs(f->GetMaximum()) >= abs(f->GetMinimum()))
    return f->GetMaximum();
  else
    return f->GetMinimum();
}

void Func1D::SetTitle(const char *title)
{
  f->SetTitle(title);
}
