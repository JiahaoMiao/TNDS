#pragma once

#include <cmath>

class RandomGen{
    public:
    RandomGen(){}
    RandomGen(unsigned int seed)
    :m_seed{seed}{}

    unsigned int getA()const {return m_a;}
    unsigned int getB()const {return m_b;}
    unsigned int getM()const {return m_m;}

    void setA(unsigned int a){m_a=a;}
    void setB(unsigned int b){m_b=b;}
    void setM(unsigned int m){m_m=m;}

    double Rand();
    double Unif(double xmin =0.,double xmax =1.);    //distribuzione uniforme
    double Exp(double mean);                 //distribuzione esponenziale
    double Gauss(double mean,double sigma);  //distribuzione gaussiana (Box-Muller)
    double GaussAR(double mean,double sigma);//distrubuzione gaussiana (Accept-Reject)
    
    private:

    unsigned int m_a{1664525},m_b{1013904223},m_m{(unsigned int)1<<31};
    unsigned int m_seed{1};

};