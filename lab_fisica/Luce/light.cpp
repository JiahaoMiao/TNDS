#include <vector>
#include <string>
#include <algorithm>

#include "Library.hpp"

#include "TApplication.h"
#include "TGraph.h"
#include "TF1.h" //1-dimensional function
#include "TF2.h" //2-dimensional function
#include "TF12.h" //A projection of a TF2 along X or Y. 
#include "TH1F.h" //1-dimensional histogram
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TLegend.h" 

using namespace std;

int main(){
    TApplication app{"app",0,0};
    
    //parametri dell'esperimento
    const double D{13.3};
    const double a{0.475};
    const double f2{0.252};
    const double c{299792458};

    //TMultiGraph mg;

    TGraph gr1,gr2,gr3;
    gr1.SetName("gr1");
    gr2.SetName("gr2");
    gr3.SetName("gr3");
    TCanvas can{"Velocita' della luce","Velocita' della luce",1600,900};
    can.cd();
    //x = omega , y = delta
      

    //[0] omega CW [1] delta CW [2] omega CCW [3] delta CCW
    vector<double> CW_x,CW_y,CCW_x,CCW_y, Both_x,Both_y;

    //Lettura dati
    Parse("CCW_after.dat",CCW_x,CCW_y);
    Parse("data_CW.dat",CW_x,CW_y);
    //Parse("data_CCW.dat",CCW_x,CCW_y);
    Parse("CW-CCW.dat",Both_x,Both_y);

    //Costruzione grafici 
    gr1.SetMarkerColorAlpha(kBlue,0.35);
    gr1.SetMarkerStyle(kFullDotSmall);
    gr1.SetMarkerSize(2);
    for(size_t i{};i<CW_x.size();i++) gr1.AddPoint(CW_x[i],CW_y[i]);
    gr2.SetMarkerColorAlpha(kRed,0.35);
    gr2.SetMarkerStyle(kFullDotSmall);
    gr2.SetMarkerSize(2);
    for(size_t i{};i<CCW_x.size();i++) gr2.AddPoint(CCW_x[i],CCW_y[i]);
    gr3.SetMarkerColorAlpha(6,0.35);//fucsia
    gr3.SetMarkerStyle(kFullDotSmall);
    gr3.SetMarkerSize(2);
    for(size_t i{};i<Both_x.size();i++) gr3.AddPoint(Both_x[i],Both_y[i]);
    
    //Funzione implicita
    double xmin{*min_element(CW_x.begin(),CW_x.end())};
    //double xmax{*max_element(Both_x.begin(),Both_x.end())};
    double xmax{12000};
    
    auto l =[&](double* x, double*p)->double {return 4*f2*D*D*x[0]/( (D+a-f2)*c );};
    TF1 implicita{ "Omega-Delta",l,xmin,xmax,0};

    //Fitting
    // TF1 myFitCW{"my fitCW","[0]+[1]*x",xmin,xmax};
    // TF1 myFitCCW{"my fitCCW","[0]+[1]*x",xmin,xmax};
    // myFitCW.SetParameters(1,0.01);
    // myFitCCW.SetParameters(1,0.01);
    // gr1.Fit(&myFitCW, "S" , "",xmin,xmax);
    // gr2.Fit(&myFitCCW, "S" , "",xmin,xmax);

    //Draw
    implicita.Draw();
    // myFitCW.Draw("SAME");
    // myFitCCW.Draw("SAME");
    //gr1.Draw("* SAME");
    gr2.Draw("* SAME");
    gr3.Draw("* SAME");
    implicita.GetXaxis()->SetTitle("Frequenza Angolare [Hz]");
    implicita.GetYaxis()->SetTitle("Delta [m]");

    TLegend legend{0.1,0.75,0.45,0.9};
    legend.SetHeader("Legenda","C"); // option "C" allows to center the header
    legend.AddEntry("Omega-Delta","Retta velocita' della luce","l");
    //legend.AddEntry("gr1","CW","p");
    legend.AddEntry("gr2","CCW dopo riposizionamento","p");
    legend.AddEntry("gr3","CW-CCW","p");
    legend.Draw();

    can.Print("Omega-Delta_focus.png");

    app.Run();
    
    return 0;
}