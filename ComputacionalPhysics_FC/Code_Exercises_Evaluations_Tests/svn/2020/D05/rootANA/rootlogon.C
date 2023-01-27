void rootlogon() {
  printf("running my rootlogon...\n");
  gInterpreter->AddIncludePath("../src/"); // permite a ROOT saber onde estão os meus include files
  //gSystem->CompileMacro("../src/point.C", "k O"); // compila a classe point
  //gSystem->CompileMacro("../src/line.C", "k O"); // compila a classe line

 // my options
  gROOT->Reset(); // reset stack objects
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111); // =0 to reset
  gStyle->SetOptTitle(0); // supress title box
  gStyle->SetOptFit(1111); // print fit results
  gStyle->SetPalette(1);
}
