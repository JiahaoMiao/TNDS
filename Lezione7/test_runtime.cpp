#include <cmath>
#include <cassert>
#include <vector>

#include "gplot++.h"
#include "fmtlib.h"
#include "funzioneBase.h"
#include "integrale.h"

int main(){
    MidPoint m{};
    Simpson s{};
    Trapezoide t{};
    Seno sin{};
    double a{0};
    double b{M_PI};
    unsigned int k{2};
    std::vector<double>prec{1e-1, 1e-2, 1e-3, 1e-4, 1e-5,1e-6,1e-7,1e-8,1e-9,1e-10,1e-11,1e-12}; //Ascisse
    std::vector<double>error(prec.size());//Ordinate

    Gnuplot plt;
    plt.redirect_to_png("Runtime_error.png","800,600");
    plt.set_logscale(Gnuplot::AxisScale::LOGXY);
    plt.set_xlabel("Precisione impostata");
    plt.set_ylabel("Precisione ottenuta");
    double appo{};

    for(unsigned int i{};i<error.size();i++){
        appo =m.integrate(a,b,sin,k,prec[i],true);
        error[i]=m.getError();
        //error[i]= fabs(appo-2.);
        //fmt::print("#{} {}\n",i,appo);
    }

    plt.plot(prec,prec,"Caso teorico peggiore",Gnuplot::LineStyle::LINESPOINTS);
    plt.plot(prec,error,"Midpoint",Gnuplot::LineStyle::LINESPOINTS);

    for(unsigned int i{};i<error.size();i++){
        appo = s.integrate(a,b,sin,k,prec[i],true);
        error[i]=s.getError();
        //error[i]= fabs(appo-2.);
        fmt::print("#{} {}\n",i,s.getError());
    }

    plt.plot(prec,error,"Simpson",Gnuplot::LineStyle::LINESPOINTS);

    for(unsigned int i{};i<error.size();i++){
        appo = t.integrate(a,b,sin,k,prec[i],true);
        error[i]=t.getError();
        //error[i]= fabs(appo-2.);
        //fmt::print("#{} {}\n",i,t.getError());
    }

    plt.plot(prec,error,"Trapezoide",Gnuplot::LineStyle::LINESPOINTS);

    plt.show();
    return 0;
}