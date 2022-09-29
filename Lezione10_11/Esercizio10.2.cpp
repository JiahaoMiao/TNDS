#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>

#include "integraleMC.h"
#include "funzioneBase.h"
#include "fmtlib.h"

int main(){
    std::ofstream fout;

    std::vector<unsigned int> nextractions{100,1000,5000,10000,50000,100000};
    
    double integrale{};
    unsigned int nrepliche{10000};

    unsigned int nthreads{16};
    int ncores_machine = omp_get_num_procs();

    fmt::print("This machine has {} cores, now usign {} threads\n",ncores_machine,nthreads);
    
    double startTime = omp_get_wtime();
    

    for(unsigned int i{};i<nextractions.size();i++){
        fmt::print("{}\n",i);

        std::string nomefile= "integrali_"+std::to_string(nextractions[i])+"_HoM.dat";
        fout.clear();
        fout.open(nomefile);
        
        //here the parallel part starts
        #pragma omp parallel num_threads( nthreads )
        {
            // a different integrator and function are built for each thread. 
            // Note that each integrator needs a different seed !

            Seno sin{};
            IntegraleMC MC{(unsigned int)omp_get_thread_num()*1000};
            
            #pragma omp for
            for(unsigned int j=0;j<nrepliche;j++){
                integrale = MC.Hit_or_Miss(0.,M_PI,1.,sin,nextractions[i]);
                #pragma omp critical//this is to ensure the correct writing to file
                {
                fout << integrale << '\n';
                }
            }
        }
        fout.close();
    }

    double stopTime = omp_get_wtime();
    double secsElapsed = stopTime-startTime;
    fmt::print("It took me {} seconds to compute {} replicas of the integral with varying number of point using {} threads\n",secsElapsed,nrepliche,nthreads);
    return 0;
}