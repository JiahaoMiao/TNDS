#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "Library.hpp"
#include "../gplot++.h"

int main(){
    std::vector<double> myx,myy,myerry;
    //Read data from file
    ParseFile("data_eom.dat",myx,myy,myerry);

    double m{},q{};
    double m1{},q1{};

    linRegPes<double>(myx,myy,myerry,&m,&q);
    linReg<double>(myx,myy,&m1,&q1);


    std::vector<double> ylin{m*myx.front()+q,m*myx.back()+q};
    std::vector<double> xlin{myx.front(),myx.back()};
    std::vector<double> y1lin{m1*myx.front()+q1,m1*myx.back()+q1};

    std::cout << "m = " << m << '\n';
    std::cout << "q = " << q << '\n';
    std::cout << "m1 = " << m1 << '\n';
    std::cout << "q1 = " << q1 << '\n';
    
    Gnuplot plot{};

    //plot.redirect_to_pdf("Rapporto_q/m.pdf");

    plot.set_xlabel("2ΔV");
    plot.set_ylabel("(rB)^2");
    plot.plot(myx,myy);
    plot.plot(xlin,ylin,"LinRegPes", Gnuplot::LineStyle::LINESPOINTS);
    plot.plot(xlin,y1lin,"LinReg", Gnuplot::LineStyle::LINESPOINTS);
    plot.plot_yerr(myx,myy,myerry);
    
    plot.show();

    return 0;
}
