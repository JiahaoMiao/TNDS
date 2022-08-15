#include "Vettore.hpp"
#include "funzioni.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>

int main(int argc,const char* argv[]){
    if(argc < 3){
        std::cerr << "Uso del programma : " << argv[0] << " <ndata> <filename>\n";
        return 1;
    }
    
    int ndata {atoi(argv[1])};
    const char* filename= argv[2];

    Vettore<double> v(Read<double>(ndata,filename));
    std::cout<<v[3]<<"\n";

    //Print(v);

    std::cout<< "media = " << std::setprecision(7)<< CalcolaMedia(v) << "\n";
    std::cout<< "varianza = " << std::setprecision(11)<< CalcolaVarianza(v) << "\n";
    std::cout<< "mediana = " << std::setprecision(7)<< CalcolaMediana(v) << "\n";

    //Print(v);
    Print(v,"data_out.txt");

    return 0;
}