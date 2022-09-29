#pragma once

#include <iostream>
#include <functional>
#include <omp.h>

#include "funzioneBase.h"
#include "funzioneScalareBase.h"
#include "randomGen.h"

class IntegraleMC{
    public:
    IntegraleMC():m_rand{}{}
    IntegraleMC(unsigned int seed)
    :m_rand{seed}{}
    ~IntegraleMC(){}

    double Hit_or_Miss(double xmin,double xmax,double fmax,FunzioneBase*f,int punti){
        int N_hit{};
        for(int i{};i<punti;i++){
            double x{m_rand.Unif(xmin,xmax)};
            double y{m_rand.Unif(0.,fmax)};
            if(y < f->Eval(x))N_hit++;
        }

        return (xmax-xmin)*fmax*N_hit/punti;
    }
    double Hit_or_Miss(double xmin,double xmax,double fmax,const std::function<double(double)>& f,int punti){
        int N_hit{};
        for(int i{};i<punti;i++){
            double x{m_rand.Unif(xmin,xmax)};
            double y{m_rand.Unif(0.,fmax)};
            if(y < f(x))N_hit++;
        }
        return (xmax-xmin)*fmax*N_hit/punti;
    }

    double Media(double xmin,double xmax,const FunzioneBase& f,int punti){
        double accu{};
        for(int i=0;i<punti;i++){
            double x{m_rand.Unif(xmin,xmax)};
            accu+= f(x);
        }
        return (xmax-xmin)*accu/punti;
    }
    double Media(double xmin,double xmax,const std::function<double(double)>& f,int punti){
        double accu{};
        for(int i{};i<punti;i++){
            double x{m_rand.Unif(xmin,xmax)};
            accu+= f(x);
        }
        return (xmax-xmin)*accu/punti;
    }
    double Media(const std::vector<double>& inf,const std::vector<double>& sup,const FunzioneScalareBase& f,int punti){
        double accu{};
        for(int i{};i<punti;i++){
            std::vector<double> v{m_rand.Unif(inf[0],sup[0]),m_rand.Unif(inf[1],sup[1])};
            accu+= f(v);
        }
        return (sup[0]-inf[0])*(sup[1]-inf[1])*accu/punti;
    }
    
    double IntegraleAVE(double xmin, double xmax, FunzioneBase * f, int punti, int ncores , unsigned int seed,double & time){

        double I = 0;
        double startTime = omp_get_wtime();
        
        // here begins the part of the code which will be executed in parallel	

        #pragma omp parallel num_threads( ncores )  
        {            
        double fmed=0;
        // note that I generate separate generators per thread. Each generators
        // needs a different seed 
        unsigned int local_seed = seed + omp_get_thread_num();
        RandomGen myGen (local_seed) ;
        unsigned int counter = 0; // this is to check how omp for works
        
        #pragma omp critical  // just a debugging thing, should not slow down too much
        {
        std::cout << "  [debug] Seed in thread " << omp_get_thread_num() << " is " << local_seed << '\n';
        }
        
        // this is the real magic 			
        #pragma omp for    
            for (int i=0; i<punti;  i++ ) { 
                fmed += f->Eval( myGen.Unif(xmin,xmax)  ) ;			
                counter++; 
        } ;

        // put everything together. critical is not needed, just to see correctly the output messages    
        #pragma omp critical     
        { 
        I = I + fmed; 
        std::cout << "  [debug] counter in thread " << omp_get_thread_num() << " ==>> " << counter << '\n';
        }        
        }
        I= I/ double(punti) * (xmax-xmin); 
        
        double stopTime = omp_get_wtime();
        time = stopTime - startTime;
        
        std::cout << "It took me " << time 
        << " seconds to compute the integral as " << I 
        << " with " << ncores << " threads " << '\n';
        
        return I ;
    
    }
    
    

    private:
    RandomGen m_rand;

};