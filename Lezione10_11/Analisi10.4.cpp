#include <vector>
#include <string>
#include <omp.h>

#include "funzioniSTL.hpp"
#include "fmtlib.h"

#include "TApplication.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TLegend.h"



int main(){
    TApplication app{"app",0,0};
    TH1F h1{"integrali_100","integrali_100",100,2,2};
    TH1F h2{"integrali_1000","integrali_1000",100,2,2};
    TH1F h3{"integrali_5000","integrali_5000",100,2,2};
    TH1F h4{"integrali_10000","integrali_10000",100,2,2};
    TH1F h5{"integrali_50000","integrali_50000",100,2,2};
    TH1F h6{"integrali_100000","integrali_100000",100,2,2};

    std::vector<unsigned int> nextractions{100,1000,5000,10000,50000,100000};
    double start = omp_get_wtime();
    for(unsigned int i{};i<nextractions.size();i++){
        std::string nomefile= "integrale_2dim_"+std::to_string(nextractions[i])+"_Media.dat";
        std::vector<double> appo = Read<double>(10000,nomefile.c_str()); 
        switch (i){
        case 0:
            for(unsigned j{};j<appo.size();j++) h1.Fill(appo[j]);
            break;
        case 1:
            for(unsigned j{};j<appo.size();j++) h2.Fill(appo[j]);
            break;
        case 2:
            for(unsigned j{};j<appo.size();j++) h3.Fill(appo[j]);
            break;
        case 3:
            for(unsigned j{};j<appo.size();j++) h4.Fill(appo[j]);
            break;
        case 4:
            for(unsigned j{};j<appo.size();j++) h5.Fill(appo[j]);
            break;
        case 5:
            for(unsigned j{};j<appo.size();j++) h6.Fill(appo[j]);
            break;
        }
    }

    TCanvas c{"Distribuzione degli integrali","Distribuzione degli integrali",1600,900};
    c.Divide(3,2);

    c.cd(1);
    h1.Draw();
    c.cd(2);
    h2.Draw();
    c.cd(3);
    h3.Draw();
    c.cd(4);
    h4.Draw();
    c.cd(5);
    h5.Draw();
    c.cd(6);
    h6.Draw();

    c.Print("Distribuzione_Integrali.png");
    double end = omp_get_wtime();
    double time = end-start;

    fmt::print("It took me {} seconds to Read from file and draw the histograms\n",time);
    //Studio ora la distribuzione delle dev.std e faccio un fit
    
    start = omp_get_wtime();
    
    TGraph g;
    g.AddPoint(100,h1.GetRMS());
    g.AddPoint(1000,h2.GetRMS());
    g.AddPoint(5000,h3.GetRMS());
    g.AddPoint(10000,h4.GetRMS());
    g.AddPoint(50000,h5.GetRMS());
    g.AddPoint(100000,h6.GetRMS());
    TCanvas c1("Distribuzione delle Dev.Std","Distribuzione delle Dev.Std",1600,900);
    TF1 myFit{"myfit","[0]/sqrt(x)",0,100000};

    fmt::print("Parameter before Fit {}\n",myFit.GetParameter(0));
    
    TFitResultPtr res = g.Fit(&myFit,"S","",0,100000);
    res->Print();
    fmt::print("Parameter after Fit {}\n",myFit.GetParameter(0));

    myFit.SetLineWidth(4);
    myFit.Draw("CP");

    TLegend leg(0.3,0.7, 0.55, 0.85) ;
    leg.AddEntry(&g,"Dati","p");
    std::string appo = "Fit "+ std::to_string(myFit.GetParameter(0))+"/sqrt(N)";
    leg.AddEntry(&myFit,appo.c_str(),"l");

    c1.cd();
    g.SetLineColor(1);
    g.SetLineWidth(4);
    g.SetLineStyle(9);
    g.SetMarkerColor(9);
    g.SetMarkerStyle(20);
    g.Draw("ALP*");
    
    leg.Draw("same");
    g.SetTitle("Distribuzione delle Dev.std");
    c1.Print("Distribuzione delle Dev.Std.png");

    end = omp_get_wtime();
    time = end-start;
    fmt::print("It took me {} seconds to Fit the graph and draw it\n",time);
    
    app.Run();
    return 0;
}