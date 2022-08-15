#include <iostream>
#include <cstdlib>

#include "puntoMateriale.h"
#include "campoVettoriale.h"
#include "fmtlib.h"


int main(int argc,char* argv[]){

    if(argc !=4){
        fmt::print("Usage:{} <x> <y> <z>\n",argv[0]);
        exit(1);
    }
    
    Posizione r{atof(argv[1]),atof(argv[2]),atof(argv[3])};

    const double e = 1.60217653e-19;
    const double me = 9.1093826e-31;
    const double mp = 1.67262171e-27;
    const double d = 1.e-10;

    PuntoMateriale elettrone{me,-e,0.,0.,d/2};
    PuntoMateriale protone{mp,e,0.,0.,-d/2};

    CampoVettoriale E = elettrone.CampoElettrico(r)+protone.CampoElettrico(r);

    fmt::print("E=({},{},{})\n",E.getFx(),E.getFy(),E.getFz());

    return 0;
}