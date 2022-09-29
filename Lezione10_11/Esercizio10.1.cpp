#include <vector>
#include <numeric>
#include <stdlib.h>
#include <iterator>

#include "randomGen.h"
#include "fmtlib.h"
#include "funzioniSTL.hpp"

#include "TApplication.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"



int main(int argc,char* argv[]){
    if(argc<2){
        fmt::print("{} N_random_numbers\n",argv[0]);
        exit(1);
    }
    int N{atoi(argv[1])};

    TApplication app("app",0,0);
    RandomGen myGen(1);

    std::vector<double> X;   //variabili aleatorie

    TH1F h1{"Distribuzione uniforme","Distribuzione uniforme",100,0,1};
    TH1F h2{"Teorema del limite centrale N=2","Teorema del limite centrale N=2",100,0,2};
    TH1F h3{"Teorema del limite centrale N=3","Teorema del limite centrale N=3",100,0,3};
    TH1F h4{"Teorema del limite centrale N=4","Teorema del limite centrale N=4",100,0,4};
    TH1F h5{"Teorema del limite centrale N=5","Teorema del limite centrale N=5",100,0,5};
    TH1F h6{"Teorema del limite centrale N=6","Teorema del limite centrale N=6",100,0,6};
    TH1F h7{"Teorema del limite centrale N=7","Teorema del limite centrale N=7",100,0,7};
    TH1F h8{"Teorema del limite centrale N=8","Teorema del limite centrale N=8",100,0,8};
    TGraph g{};

    for(int i{};i<N;i++){
        X.push_back(myGen.Unif());
        h1.Fill(X[i]);
    }
    h1.StatOverflows(true);
    g.AddPoint(1,h1.GetRMS());
    for(auto i=X.begin();i !=X.end()-1;i++){
        double appo = std::accumulate(i,i+2,0.); //non somma i+2, si ferma a i+1 
        h2.Fill(appo);
    }
    h2.StatOverflows(true);
    g.AddPoint(2,h2.GetRMS());
    for(auto i=X.begin();i!=X.end()-2;i++){
        double appo = std::accumulate(i,i+3,0.);
        h3.Fill(appo);
    }
    h3.StatOverflows(true);
    g.AddPoint(3,h3.GetRMS());
    for(auto i=X.begin();i!=X.end()-3;i++){
        double appo = std::accumulate(i,i+4,0.);
        h4.Fill(appo);
    }
    h4.StatOverflows(true);
    g.AddPoint(4,h4.GetRMS());
    for(auto i=X.begin();i!=X.end()-4;i++){
        double appo = std::accumulate(i,i+5,0.);
        h5.Fill(appo);
    }
    h5.StatOverflows(true);
    g.AddPoint(5,h5.GetRMS());
    for(auto i=X.begin();i!=X.end()-5;i++){
        double appo = std::accumulate(i,i+6,0.);
        h6.Fill(appo);
    }
    h6.StatOverflows(true);
    g.AddPoint(6,h6.GetRMS());
    for(auto i=X.begin();i!=X.end()-6;i++){
        double appo = std::accumulate(i,i+7,0.);
        h7.Fill(appo);
    }
    h7.StatOverflows(true);
    g.AddPoint(7,h7.GetRMS());
    for(auto i=X.begin();i!=X.end()-7;i++){
        double appo = std::accumulate(i,i+8,0.);
        h8.Fill(appo);
    }
    h8.StatOverflows(true);
    g.AddPoint(8,h8.GetRMS());

    TCanvas c{"Teorema_limite_centrale","Teorema_limite_centrale",1600,900};
    c.Divide(3,3);
    c.cd(1);
    h1.SetAxisRange(0,N/100+N/1000,"Y");
    h1.Draw();
    c.cd(2);
    h2.SetTitle("Distribuzione delle Somme N=2");
    h2.GetXaxis()->SetTitle("Media [AU]");
    h2.GetYaxis()->SetTitle("#");
    h2.Draw();
    c.cd(3);
    h3.SetTitle("Distribuzione delle Somme  N=3");
    h3.GetXaxis()->SetTitle("Media [AU]");
    h3.GetYaxis()->SetTitle("#");
    h3.Draw();
    c.cd(4);
    h4.SetTitle("Distribuzione delle Somme N=4");
    h4.GetXaxis()->SetTitle("Media [AU]");
    h4.GetYaxis()->SetTitle("#");
    h4.Draw();
    c.cd(5);
    h5.SetTitle("Distribuzione delle Somme N=5");
    h5.GetXaxis()->SetTitle("Media [AU]");
    h5.GetYaxis()->SetTitle("#");
    h5.Draw();
    c.cd(6);
    h6.SetTitle("Distribuzione delle Somme N=6");
    h6.GetXaxis()->SetTitle("Media [AU]");
    h6.GetYaxis()->SetTitle("#");
    h6.Draw();
    c.cd(7);
    h7.SetTitle("Distribuzione delle Somme N=7");
    h7.GetXaxis()->SetTitle("Media [AU]");
    h7.GetYaxis()->SetTitle("#");
    h7.Draw();
    c.cd(8);
    h8.SetTitle("Distribuzione delle Somme N=8");
    h8.GetXaxis()->SetTitle("Media [AU]");
    h8.GetYaxis()->SetTitle("#");
    h8.Draw();
    c.cd(9);
    g.SetTitle("Distribuzione delle Deviazione Standard");
    g.GetXaxis()->SetTitle("N");
    g.GetYaxis()->SetTitle("Dev.Std [AU]");
    g.Draw("ALP*");

    app.Run();

    return 0;
}