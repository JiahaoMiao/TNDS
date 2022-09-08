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
    Pendolo pendulum{1.};
    Runge_Kutta RK{};
    Eulero E{};

    TApplication app{"app",0,0};
    TGraph graph{};

    std::vector<double> theta;
    std::vector<double> Period;

    for(int i{};i<31;i++){
        double t{};
        theta.push_back((double)i/10);
    
        std::vector<double> x{theta[i],0.};
        double v{};
        double h{1e-2};

        while(segno(x[1])*segno(v) >= 0.){
            if(x[0] == 0 || x[0] == 2*M_PI )break;
            v = x[1];
            x = RK.Passo(t,x,pendulum,h);
            t += h;
        }
        double T{};
        if(x[0] == 0 || x[0] == 2*M_PI){
            T=0;
        }else{
            T = t - (x[1]*h)/(x[1]-v);
            T *= 2;
            fmt::print("{} {}\n",theta[i],T);
        }
        graph.AddPoint(theta[i],T);
    }

    TCanvas c;
    c.cd();
    c.SetGrid();
    graph.SetTitle("Grafico Periodo(Ampiezza iniziale)");
    graph.GetXaxis()->SetTitle("Ampiezza [rad]");
    graph.GetYaxis()->SetTitle("Periodo [s]");
    graph.Draw("ALP*");
    app.Run();
    
    return 0;
}

double segno(double x){
    return (x==0?0.:(x>0?1.:-1.));
}