#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "Library.hpp"


int main(int argc,char*argv[]){
    
    if(argc <2){
        std::cout << "Corretto utilizzo: " << *argv << " <filename>\n";
        exit(1); 
    }

    std::vector<double> v{ReadAll<double>(argv[1])};
    
    auto start{v.begin()};
    auto end{v.end()};


    //Scremaggio

    for(auto x =start ;x != end ;x++ ){
        double k_q{ round( (*x)/1.6e-19)};
        if(k_q == 0){
            v.erase(x);
            x--;
        }else{
            double appo{*x/k_q};//dovrebbe essere vicino a 1.6e-19
            std::cout << appo << "\n";
            if(appo >1.7e-19){
                v.erase(x);
                x--;
            }
        }
    }

    std::sort(v.begin(),v.end());
    Print(v.begin(),v.end(),argv[1]);

    return 0;
}