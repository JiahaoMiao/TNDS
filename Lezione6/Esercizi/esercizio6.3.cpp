#include <cmath>

#include "funzioneBase.h"
#include "solutore.h"
#include "fmtlib.h"


class Seno_meno_xCoseno:public FunzioneBase{
    public:
    Seno_meno_xCoseno()
    :m_a{1.},m_b{1.}{}
    ~Seno_meno_xCoseno(){}

    double Eval(double x) const override{
        return m_a*sin(x)-m_b*x*cos(x);
    }
    

    private:
    double m_a,m_b;
};


int main(){

    Bisezione s{};
    FunzioneBase* f{new Seno_meno_xCoseno()};
    fmt::print("Intervallo:       Zero:\n");
    for(int n{1};n<=20;n++){
        double appo = s.CercaZeri(n*M_PI,n*M_PI+M_PI_2,*f,1e-6);
        fmt::print("[{0}pi,{0}pi+pi/2]   x{0}= {1:.{2}f}\n",n,appo,15);
    }

    return 0;
}