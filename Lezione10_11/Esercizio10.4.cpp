#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>

#include "integraleMC.h"
#include "funzioneScalareBase.h"
#include "fmtlib.h"

int main(){
    std::ofstream fout;

    std::vector<unsigned int> nextractions{100,1000,5000,10000,50000,100000};
    
   
    
    const unsigned int nrepliche{10000};
    std::vector<double> inf{1.,1.};
    std::vector<double> sup{2.,2.};

    unsigned int nthreads{16};
    int ncores_machine = omp_get_num_procs();

    fmt::print("This machine has {} cores, now using {} threads\n",ncores_machine,nthreads);
    
    double startTime = omp_get_wtime();
   
    for(unsigned int i=0;i<nextractions.size();i++){
        //here the parallel part starts
        std::string nomefile= "integrale_2dim_"+std::to_string(nextractions[i])+"_Media.dat";
        fout.open(nomefile);
        
        #pragma omp parallel num_threads( nthreads )
        {
            // a different integrator and function are built for each thread. 
            // Note that each integrator needs a different seed !
            Integranda integranda{};
            IntegraleMC MC{(unsigned int)omp_get_thread_num()*1000};
            double integrale{};
    
            #pragma omp for 
            for(unsigned int j=0;j<nrepliche;j++){

                integrale = MC.Media(inf,sup,integranda,nextractions[i]);
                #pragma omp critical                //this is to ensure the correct writing to file
                {
                    fout << integrale << '\n';
                }
            }
        }
        fout.close();
    }

    double stopTime = omp_get_wtime();
    double secsElapsed = stopTime-startTime;
    fmt::print("It took me {} seconds to compute {} replicas of the multi dimensional_integral with varying number of point using {} threads\n",secsElapsed,nrepliche,nthreads);
    return 0;
}