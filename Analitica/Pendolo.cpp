#include "equazioneDifferenzialeBase.h"
#include "funzioneVettorialeBase.h"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "gplot++.h"

#include "fmtlib.h"

double segno(double x);

int main(){
    double len{1.};
    Pendolo pendulum{len};
    Runge_Kutta RK{};

    TApplication app{"app",0,0};
    TGraph graph{};

    double t{};

    std::vector<double> x{1./10.,0.};
    graph.AddPoint(x[0],x[1]);
    double h{1e-1};

    while(t<2*M_PI*sqrt(len/9.8)){
        if(x[0] == 0 || x[0] == 2*M_PI )break;
        x = RK.Passo(t,x,pendulum,h);
        t += h;
        graph.AddPoint(x[0],x[1]);
    }


    TCanvas c;
    c.cd();
    c.SetGrid();
    graph.SetTitle("Spazio degli stati(o delle fasi)");
    graph.GetXaxis()->SetTitle("x [m]");
    graph.GetYaxis()->SetTitle("v [m/s]");
    graph.Draw("ALP*");
    c.Print("Curva di fase Pensolo.png");
    app.Run();
    
    return 0;
}

double segno(double x){
    return (x==0?0.:(x>0?1.:-1.));
}