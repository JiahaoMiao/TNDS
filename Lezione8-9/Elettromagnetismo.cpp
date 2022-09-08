#include "equazioneDifferenzialeBase.h"
#include "funzioneVettorialeBase.h"
#include "fmtlib.h"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

int main(){
    //Grafico
    TApplication app{"app",0,0};
    TGraph g;
    TCanvas c("Moto in campo elettrico e magnetico uniformi","Moto in campo elettrico e magnetico uniformi");
    
    //Parametri del problema fisico
    double const q{-1.60217653e-19};
    double const me{9.1093826e-31};
    Carica carica{me,q};
    double Vx{8e6};
    double r{(me*Vx)/(q*5e-3)};
    std::vector<double> x{0.,r,0.,Vx,0.,0.};
    carica.setBz(5e-3); //Tesla
    //carica.setEx(1e4);

    //Evoluzione dell'equazione differenziale
    Runge_Kutta RK{};
    //Eulero EU{};
    double h{1e-10};
    double t{};

    int nstep{int(7.2e-9/h+0.5)};
    //int nstep{int(3e-8/h+0.5)};

    for(int i{};i<nstep;i++){
        g.SetPoint(i,x[0],x[1]);
        //fmt::print("{} {} {}\n",x[0],x[1],x[2]);
        x = RK.Passo(t,x,carica,h);
        t+=h;
    }
    fmt::print("t = {}\n",t);
    carica.printB();
    carica.printE();
    c.cd();
    g.GetXaxis()->SetTitle("x [m]");
    g.GetYaxis()->SetTitle("y [m]");
    g.Draw("ALP*");

    app.Run();

    return 0;
}