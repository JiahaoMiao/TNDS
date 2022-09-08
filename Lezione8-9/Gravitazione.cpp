#include "equazioneDifferenzialeBase.h"
#include "funzioneVettorialeBase.h"
#include "fmtlib.h"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

int main(){
    TApplication app{"app",0,0};
    TGraph graph;
    graph.GetXaxis()->SetTitle("x [m]");
    graph.GetYaxis()->SetTitle("y [m]");
    Runge_Kutta RK{};
    //Eulero Eu{};
    double h{86400};
    double t{};
    Gravitazione Grav{1.9884e30}; //Inizializzo con la massa del sole
    std::vector<double> p{-1.47098074e11,0.,0.,-3.0287e4};//Condizioni al Perielio
    //graph.SetPoint(0,p[0],p[1]);
    int i{};
    //
    while(t <= 3.1536e7){
        if(i%1==0){
            graph.SetPoint(i,p[0],p[1]);
            fmt::print("{}\n",i);
        }
        p = RK.Passo(t,p,Grav,h);
        t+= h;
        i++;
    } 
    TCanvas c1{"Gravitazione","Moto della Terra"};
    c1.cd();
    graph.SetMarkerColor(kBlue);
    graph.Draw("ALP");

    TGraph sun;
    sun.AddPoint(0.,0.);
    sun.SetMarkerStyle(kFullCircle);
    sun.SetMarkerColor(kRed);
    sun.Draw("L*");

    app.Run();
    return 0;
}