#include "IntegratorMC.h"

#include "TRandom.h"
#include "TF1.h"
#include "TH1.h"
#include "TApplication.h"
#include "TCanvas.h"

#include <cstdio>
#include <cmath>

#define TOLERANCE 1.e-1

using namespace std;

// Calcular integral com Uniform Random
void IntegratorMC::SimpleIntegration (int& N, double& value, double& error) {

  // Extremos do integral
  double xmin = GetXMin(); 
  double xmax = GetXMax();

  bool bN = true;

  if (N < 2)
    throw invalid_argument(TString::Format("[%s]: there must be at least 2 iterations!\n", __PRETTY_FUNCTION__));
  
  // Se error>0., o número de iterações (N) será determinado pelo erro relativo pretendido (error)
  if (error > 0.) {
    N = 0;
    bN = false;
  }

  // Variáveis
  double Sum = 0.;
  double SquareSum = 0.;
  double valor; // Valor utilizado no ciclo
  double error_iter = error; // Erro ao longo do ciclo
  int count = 0; //  Número de iterações ao longo do ciclo

  value = 0.5; // Para garantir que se inicia com error_iter/value > error
  
  gRandom->SetSeed(0);

  // Pus o abs recentemente->verificar
  while ((bN && count < N) || (!bN && abs(error_iter/value) > error) ) {

    valor = Eval (xmin + (xmax - xmin)*(gRandom->Uniform())); // gRandom em [xmin, xmax]

    Sum += valor;
    SquareSum += valor*valor;

    // count>1 de forma a haver mais do que apenas um ponto gerado
    if (count > 1){
      value = ((xmax-xmin)*Sum) / (count+1);
      //cout << "Value:" << value << endl;
      error_iter = ((xmax-xmin) / sqrt((double)(count+1))) * sqrt(SquareSum/(count+1) - (Sum/(count+1))*(Sum/(count+1)));
      //cout << "Error_iter:" << error_iter << endl;
    }
    
    count++;
  }

  // Valores finais
  N = count;
  error = (error_iter/value);
}

// Calcular integral com ImportanceSampling
void IntegratorMC::ImportanceSampling(int& N, double& value, double& error, const TF1& px, const TF1& xy) {
  
  bool bN = true;

  if (N < 2)
    throw invalid_argument(TString::Format("[%s]: the number of iterations must be at least 2!\n", __PRETTY_FUNCTION__));
  
  // Se error>0., o número de iterações (N) será determinado pelo erro relativo pretendido (error)
  if (error > 0.) {
    N = 0;
    bN = false;
  }


  // Variáveis
  
  // Limites do integral
  double xmin = GetXMin();
  double xmax = GetXMax();
  
  double error_iter = error; // Erro ao longo do ciclo

  // Utilizadas no ciclo
  double Fsum = 0.;
  double Fsum2 = 0.;
  double y, x, ratiof, variance;
  int count = 0;

  value = 0.5; // Para garantir que se inicia com error_iter/value > error
      
  gRandom->SetSeed(0);

  while( (bN && count < N) || (!bN && error_iter/value > error) ) {

    // check pdf normalization
    if (count == 0) {
      TF1 ftmp(px);
      //printf("integral pdf [%f, %f] = %f \n", xmin, xmax, ftmp.Integral(xmin, xmax));
    }

    //generate uniform random y
    y = gRandom->Uniform(); // [0,1]
    //cout << "y:" << y << endl;
    x = xy.Eval(y);
    //cout << "x:" << x << endl;
    //cout << "Eval(x):" << Eval(x) << endl;
    //cout << "px.Eval(x):" << px.Eval(x) << endl;
    //compute function ratio
    //if (x>=xmin && x<=xmax)
    
    ratiof = Eval(x)/px.Eval(x);

    //variance : variance = <f^2> - <f>^2
    Fsum += ratiof;
    Fsum2 += ratiof*ratiof;

    // count
    count++;
    
    //error variance: variance = <f^2> - <f>^2
    variance = Fsum2/count - (Fsum/count)*(Fsum/count);

    // Se a variance for negativa, não se poderá calcular a raiz quadrada em error_iter
    if (variance < 0.)
      break;

    if (count > 1) {
      value = Fsum/count;
      error_iter = sqrt(variance/count); // Não se multiplica por b-a pois b-a=1 depois da mudança de variáveis
    }
  }
  
  N = count;
  error = (error_iter/value);

  //printf("N=%dvalue=%ferror=%f\n",N,value,error);
}

// Calcular integral com método acceptance-rejection
void IntegratorMC::AcceptanceRejection (int& N, double& value, double& error){

  bool bN = true;
  
  // Se error>0., o número de iterações (N) será determinado pelo erro relativo pretendido (error)
  if (error > 0.) {
    N = 0;
    bN = false;
  }
  
  // Obter valores mínimos e máximos de abcissas e ordendas
  double xmin = GetXMin();
  double xmax = GetXMax();
  double fmax = f->GetMaximum();
  double fmin = f->GetMinimum();


  if (fmin < 0.)
    throw invalid_argument(TString::Format("[%s]: the function admits negative values, therefore the AcceptanceRejection method cannot be applied...\n", __PRETTY_FUNCTION__));

  else{
    double random_x; // Valor aleatório em [xmin, xmax]
    double random_f; // Valor aleatório em [0, fmax]
    int NR = 0; // Número de eventos em que random_f <= f(random_x)

    double error_iter = error; // Erro ao longo do ciclo
    int count = 0; //  Número de iterações ao longo do ciclo

    value = 0.5; // Para garantir que se inicia com error_iter/value > error

    gRandom->SetSeed(0);

    while ((bN && count < N) || (!bN && error_iter/value > error) ) {
      
      //for (int i=0; i<N; i++) {

      // Obter valor aleatório em x
      random_x = xmin + (xmax - xmin)*(gRandom->Uniform()); // gRandom gera um número em [0,1]

      // Obter valor aleatório em [0, fmax]
      random_f = fmax * (gRandom->Uniform());

      if (random_f <= Eval(random_x))
	NR++;
      //}

      // Estabeleceu-se um número mínimo razoável para NR
      if (NR > 2) {
	value = (xmax-xmin)*fmax*((double)NR/(count+1));
	error_iter = (((xmax-xmin)*fmax)/(count+1)) * sqrt (NR*(1-(double)NR/(count+1)));
      }
      count++;
      
    }

    error = error_iter/value;
    N = count;
    
  }
  
}

// Calcular integral com método acceptance-rejection com auxiliary function
void IntegratorMC::AcceptanceRejectionAuxFunc (int& N, double& value, double& error, const TF1& q, const TF1& p) {

  // Obter valores mínimos e máximos de abcissas e ordendas
  double xmin = GetXMin();
  double xmax = GetXMax();
  double fmax = f->GetMaximum();
  double fmin = f->GetMinimum();

  if (fmin < 0.)
    throw invalid_argument(TString::Format("[%s]: the function admits negative values, therefore the AcceptanceRejectionAuxFunc method cannot be applied...\n", __PRETTY_FUNCTION__));


  else{
    double uR; // u pela função U[0,1]
    double f_in_xR; // Valor xR calculado pela função f
    double q_in_xR; // Valor xR calculado pela função q
    int NR = 0; // Número de eventos em que uR <= (f_in_xR/q_in_xR)

    vector<double> randoms_xR = IntegratorMC::RandomGen (N, p); // Vetor com os xR
    
    gRandom->SetSeed(0);
    
    for (int i=0; i<N; i++) {
      uR = xmin + (xmax - xmin)*(gRandom->Uniform()); // uR
      f_in_xR = Eval(randoms_xR[i]); // f(xR)
      q_in_xR = Eval(randoms_xR[i]); // q(xR)
      
      if (uR <= f_in_xR/q_in_xR)
	  NR++;
    }

    value = (xmax-xmin)*fmax*((double)NR/N);
    //cout << "Valor: " << value << endl;
    error = (((xmax-xmin)*fmax)/N) * sqrt (NR*(1-(double)NR/N));
    //cout << "Erro: " << error << endl;
  }
}


// Calcular aleatórios em [0,1] numa função
vector<double> IntegratorMC::RandomGen (int N, const TF1& px) {
  vector<double> randoms;
  gRandom->SetSeed(0);
  for (int i=0; i<N; ++i)
    randoms.push_back(px.Eval(gRandom->Uniform()));

  return randoms;
}
