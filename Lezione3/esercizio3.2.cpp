#include "../gplot++.h"
#include "funzioniSTL.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

int main(int argc,const char*argv[]){
    if(argc<3){
        std::cerr << "Uso del programma : " << argv[0] << " <ndata> <filename>\n";
        return 1;
    }
    Gnuplot gnuplot{};
    std::vector<double> v{Read<double>(atoi(argv[1]),argv[2])};
    gnuplot.redirect_to_png("Data_Histo.png", "800,600");
    gnuplot.histogram(v,100000,"Histogram");
    gnuplot.set_xlabel("Value");
    gnuplot.set_ylabel("Number of counts");
    gnuplot.set_xrange(-10,100);
    gnuplot.set_yrange(0,10000);
    gnuplot.show();
}