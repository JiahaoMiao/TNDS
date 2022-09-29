#include "randomGen.h"
#include "fmtlib.h"

#include "TApplication.h"
#include "TH1F.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TLegend.h"



int main(){
    TApplication app("app",0,0);
    RandomGen myGen(1);
    myGen.setA(1664525);
    myGen.setB(1013904223);
    myGen.setM(1<<31);//sposta il bit nella posizione 1 alla posizione 31

    int nmax{10000};
    //THStack myStack("Distribuzioni di probabilità","Distribuzione di Probabilità");
    TH1F unif("Uniforme", "Uniforme",100,5,10);
    TH1F exp("Esponenziale","Esponenziale",100,0,10);
    TH1F gauss("Gaussiana Box-Muller","Gaussiana Box-Muller",100,-2,4);
    TH1F gaussAR("Gaussiana Accept-Reject","Gaussiana Accept-Reject",100,-2,4);
    for(int i{};i<nmax;i++){
        unif.Fill(myGen.Unif(5,10));
        exp.Fill(myGen.Exp(1));
        gauss.Fill(myGen.Gauss(1,1));
        gaussAR.Fill(myGen.GaussAR(1,1));
    }
    
    TCanvas c("PDF","Probability distribution function",1600,900);
    c.Divide(2,2);
    c.cd(1);
    unif.GetXaxis()->SetTitle("x [AU]");
    unif.GetYaxis()->SetTitle("N");
    unif.Draw();
    
    c.cd(2);
    exp.GetXaxis()->SetTitle("x [AU]");
    exp.GetYaxis()->SetTitle("N");
    exp.Draw();
    
    c.cd(3);
    gauss.GetXaxis()->SetTitle("x [AU]");
    gauss.GetYaxis()->SetTitle("N");
    gauss.Draw();

    c.cd(4);
    gaussAR.GetXaxis()->SetTitle("x [AU]");
    gaussAR.GetYaxis()->SetTitle("N");
    gaussAR.Draw();

    app.Run();

    return 0;
}