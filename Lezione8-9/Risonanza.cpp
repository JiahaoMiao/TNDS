#include <stdlib.h>

#include "equazioneDifferenzialeBase.h"
#include "funzioneVettorialeBase.h"
#include "fmtlib.h"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "timer.hpp"

int main(){
    timer time{};
    time.start();

    //Grafico con Root
    TApplication app{"app",0,0};//Per attivare l'interfaccia con l'utente
    TGraph graph{};//Per il grafico
    graph.GetXaxis()->SetTitle("Pulsazione [rad/s]");
    graph.GetYaxis()->SetTitle("Ampiezza [un. arb.]");

    //Parametri del problema fisico

    std::vector<double> omega;
    for(int i{};i<=40;i++){
        omega.push_back(9+(double)i/20);
    }
    
    double h{1e-2};//Passo h 
    Runge_Kutta RK{};
    double t{};
    int nsteps{int(90/h+0.5)};
    
    for(size_t j{};j<omega.size();j++){
        double appo{};
        std::vector<double> x{0.,0.}; //Condizioni iniziali x(0)=0 e dx(0)/dt=0
        OscillatoreArmonico osc{10.,1/30,omega[j]};//Oscillatore armonico forzato
        for(int i=0;i<nsteps;i++){
            if(appo<x[0]) appo=x[0];//Salvo il massimo
            x = RK.Passo(t,x,osc,h);
            t+=h;
        }
        graph.SetPoint(j,omega[j],appo);
    }
    time.pause();
    time.print();
    //Disegno il grafico
    TCanvas canvas{"Risonanza","Oscillatore armonico con forzante"};//Per avere uno spazio su cui disegnare(finestra grafica)
    canvas.cd(); //Restituisce il canvas appena creato
    canvas.SetGrid();
    graph.Draw("ALC*"); 
    app.Run();

    return 0;
}