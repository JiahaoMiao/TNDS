#ifndef _funzioni_h_
#define _funzioni_h_

#include <vector>
#include <string>
#include <stdlib.h>
#include <map>
#include "comune.hpp"
#include <iomanip>

#include "TGraph.h"
#include "TAxis.h"
#include "TH1F.h"


std::vector<std::string> mesi { "Gennaio", "Febbraio","Marzo","Aprile","Maggio"} ;
int c1 = 6;
int c2 = 11;

std::vector<comune> ReadFromFile ( std::string filename ) {
  
  std::cout << "===>>> Inizio lettura da file " << filename << '\n';
  
  std::vector<comune> vett ;  
  std::ifstream f ( filename ) ;  
  std::string line;    
  std::vector<int> tutti;
  
  if ( !f ) {
    std::cout << "Can't open file ! " << '\n';
    exit(-11);
  }
  
  while ( getline (f,line) ) {
    
    std::istringstream ss( line );
    std::vector <std::string> record;

    while (ss) {
      std::string s;
      if (!getline( ss, s, ',' )) break;
      record.push_back( s );
    }      

    std::vector<double> ave;
    std::vector<double> act;
    
    for ( size_t k = 0; k < mesi.size() ; k++ ) {
      ave.push_back( atof(record[c1+k].c_str())   ) ;
      act.push_back( atof(record[c2+k].c_str())   ) ;
    }
     
    comune newcomune ( record[2], record[3] , record[4] , ave, act ) ;
    vett.push_back(newcomune) ;
    
    if ( vett.size() % 1000 == 0 ) std::cout << "Finora caricati " << vett.size() << " comuni, procedo." << '\n';

  }     
  
  std::cout << "===>>> Lettura terminata : caricati " << vett.size() << " comuni." << '\n';
  
  return vett ;
  
} ;


TH1F GroupByProvincia( const std::vector<comune> & v , std::string provincia ) {

  int datasize = ( v[0].GetAveVector() ).size();

  std::vector<double> ave(datasize, 0.) ;
  std::vector<double> act(datasize, 0 ) ;

  for ( auto iter = v.begin() ; iter!=v.end() ; iter++) { 
    
    if ( iter->getProvincia() == provincia ) {
      for ( auto i = 0 ; i< datasize ; i++ ) {
	ave[i] += (iter->GetAveVector())[i];
	act[i] += (iter->GetActVector())[i] ;
      }            
    } 
  }

  TH1F myhisto("myhisto","Andamento decessi (2020)", datasize, 0, datasize+1 );
  for ( auto i = 0 ; i< datasize ; i++ ) {
    myhisto.SetBinContent(i+1,act[i]/ave[i] * 100);
    myhisto.GetXaxis()->SetBinLabel(i+1,mesi[i].c_str());
   }
  myhisto.GetYaxis()->SetTitle("Incremento (%)");
  myhisto.GetXaxis()->SetLabelSize(0.06);
  myhisto.GetXaxis()->SetTimeDisplay(1);
  myhisto.SetFillColor(kRed);
  myhisto.SetFillStyle(3003);
  
  return myhisto;

};

void Print( const std::vector<comune> & v , int nmax ) {
  
  int iter = 0;
  for ( auto it = v.begin() ; it!=v.end() ; it++ ) {
    if ( iter > nmax ) break;
    std::cout << std::setw(20) << std::left<< it->getNome() << std::setw(35) << it->getProvincia() << "   "   << std::setw(5) << it->GetAve() << " " << it->GetAct() << '\n';
    iter++;
  }
  
}

#endif