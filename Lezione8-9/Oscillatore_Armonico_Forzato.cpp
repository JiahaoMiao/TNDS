#include <stdlib.h>

#include "equazioneDifferenzialeBase.h"
#include "funzioneVettorialeBase.h"
#include "fmtlib.h"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

int main(int argc,char* argv[]){
    if(argc < 3){
        fmt::print("Usage: <{}> <Omega> <h>/n",argv[0]);
        return 1;
    }
    //Grafico con Root
    TApplication app{"app",0,0};//Per attivare l'interfaccia con l'utente
    TGraph graph{};//Per il grafico
    graph.GetXaxis()->SetTitle("Tempo [s]");
    graph.GetYaxis()->SetTitle("Posizione [m]");

    //Parametri del problema fisico
    double appo{atof(argv[1])};//Frequenza della forzante
    double h{atof(argv[2])};//Passo h 
    OscillatoreArmonico osc{10.,1/30,appo};//Oscillatore armonico forzato
    std::vector<double> x{0.,0.}; //Condizioni iniziali x(0)=0 e dx(0)/dt=0
    Runge_Kutta RK{};
    double t{};
    int nsteps{int(30/h+0.5)};
    for(int i=0;i<nsteps;i++){
        graph.SetPoint(i,t,x[0]);
        x = RK.Passo(t,x,osc,h);
        t+=h;
    }

    //Disegno il grafico
    TCanvas canvas{"Oscillatore armonico con forzante","Oscillatore armonico con forzante"};//Per avere uno spazio su cui disegnare(finestra grafica)
    canvas.cd(); //Restituisce il canvas appena creato
    canvas.SetGrid();
    graph.Draw("AL"); 
    app.Run();

    return 0;
}