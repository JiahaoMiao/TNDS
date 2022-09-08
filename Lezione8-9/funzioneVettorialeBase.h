#pragma once

#include <vector>
#include <cmath>

#include "fmtlib.h"
#include "vectorOperations.h"

class FunzioneVettorialeBase{
    public:
    virtual std::vector<double> Eval(double t,const std::vector<double> &x) const=0;
    virtual ~FunzioneVettorialeBase(){}
};

class OscillatoreArmonico:public FunzioneVettorialeBase{
    public:
    OscillatoreArmonico(double omega0):m_gamma{},m_omega{}{m_omega0=omega0;}
    OscillatoreArmonico(double omega0,double gamma):m_omega{}{
        m_omega0 = omega0;
        m_gamma = gamma;
    }
    OscillatoreArmonico(double omega0,double gamma,double omega){
        m_omega0 = omega0;
        m_gamma = gamma;
        m_omega = omega;
    }
    ~OscillatoreArmonico()override {};

    double getOmega0() const {return m_omega0;}
    double getGamma() const {return m_gamma;}
    double getOmega() const {return m_omega;}

    void setOmega0(double omega0) {m_omega0 = omega0;}
    void setGamma(double gamma) {m_gamma = gamma;}
    void setOmega(double omega) {m_omega = omega;}
    

    virtual std::vector<double> Eval(double t,const std::vector<double> &x)const override{
        if(x.size() != 2){
            fmt::print("Vector with more components than expected");
            exit(-1);
        }            
        std::vector<double> result(x.size());
        result[0]= x[1];
        result[1]= -pow(getOmega0(),2)*x[0]-getGamma()*x[1]+sin(getOmega()*t);
        
        return result;
    }

    private:
    double m_omega0{};
    double m_gamma{};
    double m_omega{};
};

class Pendolo:public FunzioneVettorialeBase{
    public:
    Pendolo(double L)
    :m_L{L}{}

    ~Pendolo() override {};

    double getL() const {return m_L;}

    void setL(double L) {m_L = L;}
    

    virtual std::vector<double> Eval(double t,const std::vector<double> &x)const override{
        if(x.size() != 2){
            fmt::print("Vector with more components than expected");
            exit(-1);
        }            
        std::vector<double> result(x.size());
        double const  g{9.81};
        result[0]= x[1];
        result[1]= -(g/m_L)*sin(x[0]);
        
        return result;
    }

    private:
    double m_L{};
};

class Gravitazione:public FunzioneVettorialeBase{
    public:
    Gravitazione(double M)
    :m_M{M}{}

    ~Gravitazione() override {}

    double getM() const {return m_M;}

    void setM(double M) {m_M = M;}
    

    virtual std::vector<double> Eval(double t,const std::vector<double> &x)const override{
        if(x.size() != 4){
            fmt::print("Vector with more components than expected");
            exit(-1);
        }            
        std::vector<double> result(x.size());
        double const  G{6.6742e-11};
        double r = sqrt(pow(x[0],2)+pow(x[1],2));
        result[0]= x[2]; //dx/dt
        result[1]= x[3]; //dy/dt
        result[2]= -G*m_M*x[0]/pow(r,3);
        result[3]= -G*m_M*x[1]/pow(r,3);
        
        return result;
    }

    private:
    double m_M{};
};

class Carica:public FunzioneVettorialeBase{
    public:
    Carica(double M,double q)
    :m_M{M},m_q{q}{}
    Carica(double M,double q,std::vector<double> E,std::vector<double> B)
    :m_M{M},m_q{q},m_E{E},m_B{B}{}

    ~Carica() override {}

    double getM() const {return m_M;}
    double getC() const {return m_q;}
    
    double getEx() const {return m_E[0];}
    double getEy() const {return m_E[1];}
    double getEz() const {return m_E[2];}

    double getBx() const {return m_B[0];}
    double getBy() const {return m_B[1];}
    double getBz() const {return m_B[2];}

    void setM(double M) {m_M = M;}
    void setq(double q) {m_q = q;}

    void setEx(double Ex){m_E[0]=Ex;}
    void setEy(double Ey){m_E[1]=Ey;}
    void setEz(double Ez){m_E[2]=Ez;}

    void setBx(double Bx){m_B[0]=Bx;}
    void setBy(double By){m_B[1]=By;}
    void setBz(double Bz){m_B[2]=Bz;}

    void printB()const{
        fmt::print("B = ({},{},{})\n",getBx(),getBy(),getBz());
    }
    void printE()const{
        fmt::print("E = ({},{},{})\n",getEx(),getEy(),getEz());
    }

    virtual std::vector<double> Eval(double t,const std::vector<double> &x)const override{
        if(x.size() != 6){
            fmt::print("Vector with more components than expected");
            exit(-1);
        }
        if(m_E.size() != 3){
            fmt::print("Vector E with wrong number of components than expected");
            exit(-1);
        }
        if(m_B.size() != 3){
            fmt::print("Vector B with wrong number of components than expected");
            exit(-1);
        }                   
        std::vector<double> result(x.size());
        double k{m_q/m_M};
        result[0]= x[3]; //dx/dt
        result[1]= x[4]; //dy/dt
        result[2]= x[5]; //dz/dt

        result[3]= k*(x[4]*getBz()-x[5]*getBy()+getEx()); //yz-zy
        result[4]= k*(x[5]*getBx()-x[3]*getBz()+getEy()); //zx-xz
        result[5]= k*(x[3]*getBy()-x[4]*getBx()+getEz()); //xy-yx

        //fmt::print("res = {} {} {} {} {} {}\n", result[0],result[1],result[2],result[3],result[4],result[5]);
        return result;
    }

    private:
    double m_M{},m_q{};
    std::vector<double> m_E{0.,0.,0.},m_B{0.,0.,0.};
};