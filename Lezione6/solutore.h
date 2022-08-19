#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include "funzioneBase.h"


double segno(double x);

//Funzione che calcola la derivata prima di una funzione nel punto x e un incremento h
double derivata(const FunzioneBase &f,double x, double h=1e-3,int n=1);
double derivata(std::function<double(double)>f,double x, double h=1e-3,int n=1);

// ==================================
// Classe Solutore
// ==================================

class Solutore{
    public:

    Solutore()
    :m_a{},m_b{},m_prec(),m_nmax{},m_niterations{}{}
    Solutore(double prec)
    :m_a{},m_b{},m_prec(prec),m_nmax{},m_niterations{}{}
    virtual ~Solutore();

    virtual double CercaZeri(double xmin,double xmax,const FunzioneBase& f,double prec=1e-3,unsigned int nmax =100)=0;
    virtual double CercaZeri(double xmin,double xmax,std::function<double (double)>f,double prec=1e-3,unsigned int nmax =100)=0;

    void SetPrecisione(double epsilon){m_prec=epsilon;}
    double GetPrecisione(){return m_prec;}
    void SetNMaxiterations(unsigned int n){m_nmax=n;}
    unsigned int GetNMaxiterations(){return m_nmax;}
    unsigned int GetNiterations(){return m_niterations;}

    virtual bool Trovato() const = 0; //di default è falso
    virtual double Incertezza()const = 0;

    protected:
    double m_a,m_b;
    double m_prec;
    unsigned int m_nmax,m_niterations;
    bool m_found = false;
};

// ==================================
// Classe Bisezione
// ==================================
class Bisezione:public Solutore{
    public:

    Bisezione();
    Bisezione(double prec);
    virtual ~Bisezione();

    double CercaZeri(double xmin,double xmax,const FunzioneBase& f,double prec=1e-3,unsigned int nmax =100) override;
    double CercaZeri(double xmin,double xmax,std::function<double(double)> f,double prec=1e-3,unsigned int nmax =100) override;
    
    bool Trovato() const override;
    double Incertezza()const override;
};

// ==================================
// Classe Secante
// ==================================
class Secante:public Solutore{
    public:

    Secante();
    Secante(double prec);
    virtual ~Secante();

    double CercaZeri(double xmin,double xmax,const FunzioneBase& f,double prec=1e-3,unsigned int nmax =100) override;
    double CercaZeri(double xmin,double xmax,std::function<double(double)> f,double prec=1e-3,unsigned int nmax =100) override;
    
    bool Trovato() const override;
    double Incertezza()const override;
};

// ==================================
// Classe Newton
// ==================================

class Newton:public Solutore{
    public:

    Newton();
    Newton(double prec);
    virtual ~Newton();

    double CercaZeri(double xmin,double xmax,const FunzioneBase& f,double prec=1e-3,unsigned int nmax =100) override;
    double CercaZeri(double xmin,double xmax,std::function<double(double)> f,double prec=1e-3,unsigned int nmax =100) override;

    bool Trovato() const override;
    double Incertezza()const override;
};