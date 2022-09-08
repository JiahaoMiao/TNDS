#include <string>
#include <cassert>

#include "equazioneDifferenzialeBase.h"
#include "fmtlib.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "gplot++.h"

bool are_close(double calculated,double expected, double epsilon =1e-9){
    return fabs(calculated-expected)<epsilon;
}


int main(int argc,char* argv[]){
    if(argc !=2){
        fmt::print("Usage: <{}> <stepsize>\n",argv[0]);
        return -1;
    }
    TApplication myapp("myApp",0,0);

    Eulero myEuler{};
    Runge_Kutta myRK{};

    OscillatoreArmonico osc(1.);
    double tmax{70.};
    double h{atof(argv[1])};
    std::vector<double> x{0.,1.};//smorzato
    double t{0.};
    TGraph myGraph{};

    int nstep{int(tmax/h+0.5)};
    fmt::print("{}\n",nstep);
    for(int i{};i<nstep;i++){
        myGraph.SetPoint(i,t,x[0]);
        //x = myEuler.Passo(t,x,osc,h);
        x=myRK.Passo(t,x,osc,h);
        t+=h;
    }
    //assert(are_close(x[0], 19.773746013860173));
    //assert(are_close(x[1], 25.848774751522960));
    fmt::print("{:0.20f}\n",x[0]);
    fmt::print("{:0.20f}\n",x[1]);
    assert(are_close(x[0], 0.7738501114078689));
    assert(are_close(x[1], 0.6333611095194112));

    TCanvas c;
    c.cd();
    std::string  title = "Oscillatore armonico (Eulero h = " + std::to_string(h) + ")";
    myGraph.SetTitle(title.c_str());
    myGraph.GetXaxis()->SetTitle("Tempo [s]");
    myGraph.GetYaxis()->SetTitle("Posizione x [m]");
    myGraph.Draw("AL");

    myapp.Run();
    return 0;
}