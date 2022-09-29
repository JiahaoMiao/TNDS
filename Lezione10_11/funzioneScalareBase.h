#pragma once

#include <cmath>
#include <vector>


class FunzioneScalareBase{
    public:
    virtual double Eval(const std::vector<double>& v) const=0;
    virtual ~FunzioneScalareBase(){}
    double operator()(const std::vector<double> v) const{
        return Eval(v);
    }
};

class Integranda:public FunzioneScalareBase{
    public:
    Integranda(){}
    ~Integranda(){}
    
    double Eval(const std::vector<double>& v) const override{
        return 5*cos(4*v[1])*sin(7*v[0])/(v[0]*v[0])+10;
    }//Modificare l'integranda
};