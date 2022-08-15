#include "string"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include "algorithm"

#include "comune.hpp"
#include "funzioni_comune.hpp"

#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TPaveLabel.h"

using namespace std;

// funzione boolena utilizza nel sort per riordinare elementi in base 
// all'incremento di decessi rispetto alla media 

bool mymax(comune i, comune j) { return i.getRatio()>j.getRatio(); };

int main () {

  TApplication app("myApp",0,0);
  gStyle->SetOptStat(kFALSE);

  // lettura dati : informazioni organizzate in un vector di comuni
  
  vector<comune> vettore_comune = ReadFromFile ("covid19.csv");
  //int ncomuni = vettore_comune.size();

  string provincia = "Milano";

  // guarda l'andamento in una provincia
  
  TH1F mygr = GroupByProvincia( vettore_comune, provincia ) ;

  // plots
  
  TCanvas can;
  can.cd();
  mygr.Draw();
  string lab = provincia + " 2020 (ISTAT)" ;
  TPaveLabel pl(0.15,0.7,0.4,0.8,lab.c_str(),"NDC") ;
  pl.SetBorderSize(0);
  pl.SetFillColor(10);
  pl.Draw("same");
 
  // Ordina i comuni in base al maggior incremento relativo di decessi

  sort ( vettore_comune.begin(), vettore_comune.end(), mymax ) ;

  // Stampa il vettore di comuni riordinato

  Print ( vettore_comune, 20 ) ;
  
  app.Run();
  
}
