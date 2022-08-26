#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include "funzioneBase.h"

class Integral{
    public:
    Integral():m_a{},m_b{},m_sign{},m_step(),m_prec{},m_err{}{}

    double integrate(double a,double b,const FunzioneBase &f,unsigned int nstep=1e3,double precision=1e-6,bool fixed_precision=false){
        checkInterval(a,b);
        setPrecision(precision);
        setPartition(nstep);
        setError(0);
        if(fixed_precision == true){
            return calculate(f);
        }else{
            return calculate(nstep,f);
        }
    }

    double integrate(double a,double b,std::function<double(double)> f,unsigned int nstep=1e3,double precision=1e-6,bool fixed_precision=false){
        checkInterval(a,b);
        setPrecision(precision);
        setPartition(nstep);
        setError(0);
        if(fixed_precision == true){
            return calculate(f);
        }else{
            return calculate(nstep,f);
        }
    }
    

    double getA() const {return m_a;}
    double getB() const {return m_b;}
    int getSign() const {return m_sign;}
    unsigned int getPartition() const {return m_step;}
    double getError() const {return m_err;}
    double getPrecision() const {return m_prec;}

    void setA(double a) {m_a=a;}
    void setB(double b)  {m_b=b;}
    void setSign(int s) {m_sign=s;}
    void setPartition(unsigned int n) {m_step=n;}
    void setError(double err) {m_err=err;}
    void setPrecision(double p) {m_prec=p;}

    
    private:

    virtual double calculate(unsigned int nstep,const FunzioneBase &f)const =0;
    virtual double calculate(unsigned int nstep,std::function<double(double)> f)const=0;

    virtual double calculate(const FunzioneBase &f) =0;
    virtual double calculate(std::function<double(double)> f)=0;
    void checkInterval(double a,double b){
        m_a=std::min(a,b);
        m_b=std::max(a,b);
        m_sign= (a<b) ? 1 : -1;
    }

    double m_a,m_b;
    int m_sign;
    unsigned int m_step;
    double m_prec;
    double m_err;
};

class MidPoint:public Integral{
    public:
    MidPoint():Integral(){}

    private:

    // ================================================
    // Fixed Partition
    // ================================================

    double calculate(unsigned int nstep,const FunzioneBase &f)  const override{
        double h{(getB()-getA())/nstep};
        double sum{};

        for(unsigned int i{};i<nstep;i++){
            sum+= f.Eval(getA()+(i+0.5)*h);
        }

        return getSign()*sum*h;
    }

    double calculate(unsigned int nstep,std::function<double(double)>f) const override{
        double h{(getB()-getA())/nstep};
        double sum{};

        for(unsigned int i{};i<nstep;i++){
            sum+= f(getA()+(i+0.5)*h);
        }

        return getSign()*sum*h;
    }
    // ================================================
    // Fixed Precision 
    // ================================================
    virtual double calculate(const FunzioneBase &f)override{
        double old_sum{};
        double sum{calculate(getPartition(),f)};

        do{
            old_sum=sum;
            setPartition(2*getPartition());
            sum = calculate(getPartition(),f);
            setError(4*fabs(sum-old_sum)/3);
        }while(getError()>getPrecision());
        //return sum;
        return (4*sum-old_sum)/3;
    }
    virtual double calculate(std::function<double(double)> f)override{
        double old_sum{};
        double sum{calculate(getPartition(),f)};
        
        do{
            old_sum=sum;
            setPartition(2*getPartition());
            sum = calculate(getPartition(),f);
            setError(4*fabs(sum-old_sum)/3);
        }while(getError()>getPrecision());

        return (4*sum-old_sum)/3;
    }
};


class Simpson:public Integral{
    public:
    Simpson():Integral(){}

    private:
    // ================================================
    // Fixed Partition 
    // ================================================

    double calculate(unsigned int nstep,const FunzioneBase &f) const override{
        unsigned int truen = (nstep %2==0) ? nstep:(nstep-1);
        double h{(getB()-getA())/truen};
        double sum{(f.Eval(getA())+ f.Eval(getB()))/3};

        for(unsigned int i{1};i<truen;i++){
            sum+= 2*(1+i%2)*f.Eval(getA()+i*h)/3;
        }
        return getSign()*sum*h;
    }

    double calculate(unsigned int nstep,std::function<double(double)>f) const override{
        unsigned int truen = (nstep %2 ==0) ? nstep:(nstep-1);
        double h{(getB()-getA())/truen};
        double sum{(f(getA())+ f(getB()))/3};

        for(unsigned int i{1};i<truen;i++){
            sum+= 2*(1+i%2)*f(getA()+i*h)/3;
        }
        return getSign()*sum*h;
    }

    // ================================================
    // Fixed Precision 
    // ================================================
    virtual double calculate(const FunzioneBase &f)override{
        double old_sum{};
        double sum{calculate(getPartition(),f)};

        do{
            old_sum=sum;
            setPartition(2*getPartition());
            sum = calculate(getPartition(),f);
            setError(16*fabs(sum-old_sum)/15);
        }while(getError()>getPrecision());
        //return sum;
        return (16*sum-old_sum)/15;
        //return (4*sum-old_sum)/3;
    }
    virtual double calculate(std::function<double(double)> f)override{
        double old_sum{};
        double sum{calculate(getPartition(),f)};

        do{
            old_sum=sum;
            setPartition(2*getPartition());
            sum = calculate(getPartition(),f);
            setError(16*fabs(sum-old_sum)/15);
        }while(getError()>getPrecision());

        return (16*sum-old_sum)/15;
    }
};

class Trapezoide:public Integral{
    public:
    Trapezoide():Integral(){}

    private:
    // ================================================
    // Fixed Partition 
    // ================================================

    double calculate(unsigned int nstep,const FunzioneBase &f)const override{
        //Parametri iniziali
        nstep = (nstep%2==0) ? nstep : (nstep-1);
        double sum{(f.Eval(getA())+f.Eval(getB()))/2};
        double h{(getB()-getA())/nstep};  //Passo h
        for(unsigned int i{1};i<nstep;i++){
            sum+= f.Eval(getA()+i*h);
        }
        return getSign()*sum*h;
    }


    double calculate(unsigned int nstep,std::function<double(double)>f)const override{

        nstep = (nstep%2==0) ? nstep : (nstep-1);
        double sum{(f(getA())+f(getB()))/2};
        double h{(getB()-getA())/nstep};  //Passo h
        for(unsigned int i{1};i<nstep;i++){
            sum+= f(getA()+i*h);
        }
        return getSign()*sum*h;
    } 

    // ================================================
    // Fixed Precision 
    // ================================================
    //Versione ottimizzata che tiene conto del calcolo precedente
    virtual double calculate(const FunzioneBase &f) override{
        double old_Int{};// Integrale per h/2
        double h{(getB()-getA())/getPartition()};
        double sum{(f.Eval(getA())+f.Eval(getB()))/2};
        std::cout<< "Errore iniziale = " << getError() << '\n';
        double Int{}; //Valore dell'integrale 
        do{

            old_Int=Int;                                  //Salvo la somma precedente
            h = (getB()-getA())/getPartition();           //Dimezzo il passo h
            for(unsigned int i{1};i<getPartition();i++){  //k sempre pari, quindi salto i=0
                int A = (i%2 == 0) ? 0 : 1;              //I pari sono gia' presenti nella sommatoria
                sum+= A*f.Eval(i*h);
            }
            Int=sum*h;
            setError(4*fabs(Int-old_Int)/3); //Aggiorno il nuovo errore
   
            setPartition(2*getPartition());//raddoppio il numero di intervalli
        
        }while(getError()>getPrecision());
        //return sum;
        return (4*Int-old_Int)/3;
    }

    virtual double calculate(std::function<double(double)> f) override{
        double old_Int{};// Integrale per h/2
        double h{(getB()-getA())/getPartition()};
        double sum{(f(getA())+f(getB()))/2};
        std::cout<< "Errore iniziale = " << getError() << '\n';
        double Int{}; //Valore dell'integrale 
        do{

            old_Int=Int;                                  //Salvo la somma precedente
            h = (getB()-getA())/getPartition();           //Dimezzo il passo h
            for(unsigned int i{1};i<getPartition();i++){  //k sempre pari, quindi salto i=0
                int A = (i%2 == 0) ? 0 : 1;               //I pari sono gia' presenti nella sommatoria
                sum+= A*f(i*h);
            }
            Int=sum*h;
            setError(4*fabs(Int-old_Int)/3);              //Aggiorno il nuovo errore
   
            setPartition(2*getPartition());               //raddoppio il numero di intervalli
        
        }while(getError()>getPrecision());
        //return sum;
        return (4*Int-old_Int)/3;
    }
    
    /*
    virtual double calculate(const FunzioneBase &f) override{
        double old_sum{};
        double sum{calculate(getPartition(),f)};

        do{
            old_sum=sum;
            setPartition(2*getPartition());
            sum = calculate(getPartition(),f);
            setError(4*fabs(sum-old_sum)/3);
        }while(getError()>getPrecision());
        //return sum;
        return (4*sum-old_sum)/3;
    }
    virtual double calculate(std::function<double(double)> f) override{
        double old_sum{};
        double sum{calculate(getPartition(),f)};

        do{
            old_sum=sum;
            setPartition(2*getPartition());
            sum = calculate(getPartition(),f);
            setError(4*fabs(sum-old_sum)/3);
        }while(getError()>getPrecision());

        return (4*sum-old_sum)/3;
    }*/
};
