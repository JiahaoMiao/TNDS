#include <cmath>

#include "randomGen.h"
#include "attritoViscoso.h"
#include "fmtlib.h"
#include <fstream>

#include "TApplication.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"


int main(){
    TApplication app{"app",0,0};
    TCanvas c1{"Coefficiente di Attrito viscono","Esperimento Attrito",1600,900};

    //Parametri Esperimento

    const double rho{2700};//kg/m^3
    const double rho_0{1250};//kg/m^3
    const double x{0.4};//m
    const double eta{0.83};//kg/ms
    const double R{0.005};//m
    const double sigmat{0.01},sigmax{0.001},sigmaR{0.0001};

    AttritoViscoso V{rho,rho_0,x,R,eta,sigmat,sigmax,sigmaR};
    V.Esegui();
    V.Analizza();

    double sigma_eta{eta*sqrt(pow(2*sigmaR/R,2)+pow(sigmat/V.getT(),2)+pow(sigmax/x,2))};

    TH1F etahist{"Distribuzione di eta","Distribuzione di eta",100,eta-3*sigma_eta,eta+3*sigma_eta};
    etahist.StatOverflows(true);
    for(int i{};i<1000;i++){
        V.Esegui();
        V.Analizza();
        etahist.Fill(V.getEtamis());
    }
    
    fmt::print("sigma_eta = {}\n",sigma_eta);

    c1.cd();
    etahist.GetXaxis()->SetTitle("eta [kgm^-1s^-1]");
    etahist.GetYaxis()->SetTitle("N");
    etahist.Draw();
    app.Run();
    return 0;
}