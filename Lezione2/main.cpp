#include "Vettore.h"
#include "funzioni.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "timer.hpp"

int main(int argc,const char* argv[]){
    if(argc < 3){
        std::cerr << "Uso del programma : " << argv[0] << " <ndata> <filename>\n";
        return 1;
    }
    timer t{};
    
    int ndata = atoi(argv[1]);
    const char* filename= argv[2];

    Vettore v(Read(ndata,filename));
    std::cout<<v[3]<<"\n";
   
    std::cout<< "media = " << std::setprecision(7)<< CalcolaMedia(v) << "\n";
    std::cout<< "varianza = " << std::setprecision(11)<< CalcolaVarianza(v) << "\n";

  
    std::cout<< "mediana = " << std::setprecision(7)<< CalcolaMediana(v) << "\n";
    
    t.start();
    merge_sort(v,0,v.GetN()-1);
    //quicksort(v,0,v.GetN()-1);
    t.pause();
    t.print();

    //Print(v);
    Print(v,"data_out.txt");
    return 0;
}