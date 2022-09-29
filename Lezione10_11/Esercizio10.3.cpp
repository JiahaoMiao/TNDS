#include <fstream>
#include <omp.h>

#include "integraleMC.h"
#include "funzioneScalareBase.h"
#include "funzioneBase.h"
#include "fmtlib.h"

#include "TApplication.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TCanvas.h"



int main(){
    TApplication app{"app",0,0};
    //Integranda integranda{};
    Seno integranda{};
    IntegraleMC MC{};
    //std::vector<double> inf{1.,1.};
    //std::vector<double> sup{2.,2.};
    double xmin{0.};
    double xmax{M_PI};
    int punti{20000000};
    
    //double integrale = MC.Media(inf,sup,integranda,punti);
    int ncores_machine = omp_get_num_procs() ;
    int nmax_threads = ncores_machine + 2;
    double time{};

    std::cout << "This machine has " <<  ncores_machine << " cores" << '\n';
    std::cout << "Will try with up to " << nmax_threads << " threads" << '\n';

    unsigned int seed = 1;
    TGraph h;

    for ( int ncores = 1 ; ncores <= nmax_threads ; ncores ++) {
        std::cout << ncores << '\n';
        double integrale = MC.IntegraleAVE(xmin,xmax,&integranda, punti , ncores, seed,time);
        h.AddPoint(ncores,time);
    }

    TCanvas c;
    c.cd();
    h.SetTitle("Calcolo Integrale sin(x) generando 20 milioni di punti");
    h.GetXaxis()->SetTitle("#Threads");
    h.GetYaxis()->SetTitle("Time_Elapsed [s]");
    h.Draw("ALP*");
    c.Print("Test_#Threads.png");
    
    app.Run();
    return 0;
}