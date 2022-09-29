#include "randomGen.h"

double RandomGen::Rand(){
    m_seed = (m_a*m_seed+m_b)%m_m;
    return m_seed;
}
double RandomGen::Unif(double xmin,double xmax){      //distribuzione uniforme
    return xmin + (xmax-xmin)*(double)Rand()/m_m;
}
double RandomGen::Exp(double mean){                   //distribuzione esponenziale
    return -log(1-Unif())/mean;
}
double RandomGen::Gauss(double mean,double sigma){    //distribuzione gaussiana (Box-Muller)
    double s{Unif()};
    double t{Unif()};
    double x{sqrt(-2.*log(1.-s))*cos(2.*M_PI*t)};
    return mean+x*sigma;
}
double RandomGen::GaussAR(double mean,double sigma){  //distrubuzione gaussiana (Accept-Reject)
    double x{},y{},chi{};
    do{
    x = Unif(mean-3*sigma,mean+3*sigma);
    y = Unif(0.,1./(sqrt(2*M_PI)*sigma));
    chi = pow((x-mean)/sigma,2);
    }while( y > exp(-chi/2)/(sqrt(2*M_PI)*sigma));
    return x;
}