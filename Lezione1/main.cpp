#include <iostream>
#include <stdlib.h>
#include "funzioni.h"


int main(int argc,const char * argv[]){
    if(argc <3){
        std::cerr <<  "Uso del programma: " << argv[0] << "<size> <filename>\n";
        return 1;
    }

    int size = atoi(argv[1]);
    const char *filename = argv[2];

    double * data= ReadDataFromFile(filename,&size);

    int ndati;
    std::cout << "Digita quanti elementi vuoi vedere";

    do{
        std::cin >> ndati;
    }while(ndati<0 and ndati>size);
    

    Print(data,ndati);

    std::cout <<"Media= " << std::setprecision(8) << CalcolaMedia(data,size)<< "\n";
    std::cout <<"Mediana= "<< std::setprecision(8) << CalcolaMediana(data,size) << "\n";
    std::cout <<"Varianza= " << std::setprecision(8) << CalcolaVarianza(data,size) << "\n";

    Print("fileout.txt",data,size);

    delete[] data;

    return 0;
}