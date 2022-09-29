#include <iostream>
#include <cmath>
#include <omp.h>

#include "funzioneBase.h"
#include "integraleMC.h"


int main(){

    #pragma omp parallel 
    {
        Seno sin{};
        IntegraleMC MC{};

        #pragma omp for
        for(int i=0;i<10;i++){
            double integrale = MC.Media(0.,M_PI,sin,500);
            #pragma omp critical
            {
            std::cout << "#"<< i << " Thread #" << omp_get_thread_num()<<" integrale = " << integrale << '\n'; 
            }
        }
        
        
    }
    
    
    

    

    return 0;
}