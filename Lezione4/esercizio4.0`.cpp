#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "TGraphErrors.h"
#include "TApplication.h"
#include "TF1.h"
#include "TAxis.h"
#include "TLegend.h"

#include "Library.hpp"


TGraphErrors DoPlot( std::vector<double> myx, std::vector<double> myy , std::vector<double> myerry ) {

  TGraphErrors mygraph;

  for ( size_t k = 0 ; k < myx.size() ; k++ ) {    
    mygraph.SetPoint(k, myx[k] , myy[k] );
    mygraph.SetPointError(k, 0, myerry[k]);
  };

  return mygraph;
  
}

int main() {
  
  TApplication app("MyApp",0,0);

  std::vector<double> myx, myy, myerry;

  // read data from file

  ParseFile("data_eom.dat", myx, myy, myerry ) ;

  // create TGraphErrors

  TGraphErrors mygraph{DoPlot(myx, myy, myerry)};

  // fit the TGraphErrors ( linear fit )

  TF1 * myfun{new TF1 ("fitfun","[0]*x+[1]",0, 1000)};
  mygraph.Fit(myfun);
  double moe{myfun->GetParameter(0)};
  double error{sqrt(  pow (1./moe, 4) * pow(myfun->GetParError(0),2)  ) } ;

  std::cout << "Valore di e/m dal fit = " << 1./moe << "+/-" << error << '\n';
  std::cout << "Valore del chi2 del fit = " << myfun->GetChisquare() << '\n';
  std::cout << "          prob del chi2 = " << myfun->GetProb() << '\n';

  // customise the plot, cosmetics

  mygraph.Draw("AP");
  mygraph.SetMarkerStyle(20);
  mygraph.SetMarkerSize(1);
  mygraph.SetTitle("Misura e/m");
  mygraph.GetXaxis()->SetTitle("2#DeltaV (V)");
  mygraph.GetYaxis()->SetTitle("(B_{z}R)^{2} (T^{2}m^{2} )");
  TLegend leg (0.15,0.7, 0.3, 0.85) ;
  leg.AddEntry(&mygraph,"data","p");
  leg.AddEntry(myfun,"fit","l");
  leg.Draw("same");

  app.Run();
 
  return 0;
  
}
