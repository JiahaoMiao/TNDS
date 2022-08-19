#include <cmath>

#include "funzioneBase.h"
#include "solutore.h"
#include "fmtlib.h"


int main(){

    //Bisezione b{};
    //Secante b{};
    Newton b{};
    fmt::print("Intervallo:       Zero:\n");
    for(int n{1};n<=20;n++){
        double appo = b.CercaZeri(n*M_PI,n*M_PI+M_PI_2,[](double x)->double{return sin(x)-x*cos(x);},1e-6);
        fmt::print("[{0}pi,{0}pi+pi/2]   x{0}= {1:.{2}f} {3}\n ",n,appo,15,b.GetNiterations());
    }

    double appo= derivata([](double x)->double{return sin(x)-x*cos(x);},0);
    fmt::print("Derivata in 0:{}\n",appo);

    return 0;
}