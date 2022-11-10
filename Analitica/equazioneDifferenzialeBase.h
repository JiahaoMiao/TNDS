#pragma once

#include <vector>
#include "funzioneVettorialeBase.h"
#include "vectorOperations.h"

class EquazioneDifferenzialeBase{
    public:
    virtual ~EquazioneDifferenzialeBase(){}
    virtual std::vector<double> Passo(double t,const std::vector<double> &x, const FunzioneVettorialeBase &f,double h) const =0;
};

class Eulero : public EquazioneDifferenzialeBase{
    public:
    ~Eulero()override{}
    virtual std::vector<double> Passo(double t,const std::vector<double> &x,const FunzioneVettorialeBase &f,double h) const override{
        return x+(f.Eval(t,x))*h;
    }
};

class Runge_Kutta: public EquazioneDifferenzialeBase{
    public:
    ~Runge_Kutta()override{}
    virtual std::vector<double> Passo(double t,const std::vector<double> &x,const FunzioneVettorialeBase &f,double h) const override{
        std::vector<double> k1,k2,k3,k4;
        k1 = f.Eval(t,x);
        k2 = f.Eval(t+h/2,x+k1*h/2.);
        k3 = f.Eval(t+h/2,x+k2*h/2.);
        k4 = f.Eval(t+h,x+k3*h);
        return x+h*(k1+2.*k2+2.*k3+k4)/6.;
    }
};