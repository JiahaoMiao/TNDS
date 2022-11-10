#include <string>
#include <iostream>

#include "equazioneDifferenzialeBase.h"
#include "funzioneVettorialeBase.h"
#include "fmtlib.h"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h" 
#include "TMultiGraph.h"
#include "TLegend.h"

void Draw(TCanvas& c,TGraph & graph,EquazioneDifferenzialeBase& ODE_solver,FunzioneVettorialeBase& eq_diff,std::vector<double> & init_cond,unsigned int n);

int main(){
    TApplication app{"app",0,0};
    Gravitazione Grav{1.9884e30}; //Inizializzo con la massa del sole
    Runge_Kutta RK{};
    
    TCanvas c1{"Gravitazione","Moto della Terra",2500,2200};
    TGraph sun{};
    sun.SetPoint(0,0.,0.);
    sun.SetMarkerStyle(kFullCircle);
    sun.SetMarkerColor(kRed);
    c1.Divide(3,3);
    
    TGraph graph[9];
    
    for(unsigned int i{1};i<=(unsigned int)9;i++){
        std::vector<double> initial_condition{-1.47098074e11,0.,0.,-3.0287e4};//Condizioni al Perielio
        Draw(c1,graph[i-1],RK,Grav,initial_condition,i);
        sun.Draw("L*");
    }
    c1.Print("Campo_1/r^3.png");

    app.Run();
    
    return 0;
}

void Draw(TCanvas& c,TGraph & graph,EquazioneDifferenzialeBase& ODE_solver,FunzioneVettorialeBase& eq_diff,std::vector<double> & init_cond,unsigned int n){
    c.cd(n);

    std::string appo{"Orbita dopo "+std::to_string((n+1)*10)+" anni"};
    graph.SetTitle(appo.c_str());

    double h{86400};
    double t{};

    while(t <= (n+1)*10*3.1536e7){    
        graph.AddPoint(init_cond[0],init_cond[1]);
        init_cond = ODE_solver.Passo(t,init_cond,eq_diff,h);
        t+= h;
    }
    
    graph.GetXaxis()->SetTitle("x [m]");
    graph.GetYaxis()->SetTitle("y [m]");
    graph.SetMarkerColor(kBlue);
    graph.Draw("ALP");
}