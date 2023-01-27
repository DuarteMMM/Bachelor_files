void rootlogon() {
  printf("running my rootlogon...\n");
  gInterpreter->AddIncludePath("../src/");
  gSystem->CompileMacro("../src/DataReader.C", "k O");
  gSystem->CompileMacro("../src/DataManip.C", "k O");

 // my options
  gROOT->Reset(); // reset stack objects
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111); // =0 to reset
  gStyle->SetOptTitle(0); // supress title box
  gStyle->SetOptFit(1111); // print fit results
  gStyle->SetPalette(1);
}
