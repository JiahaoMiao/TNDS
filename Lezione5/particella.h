#pragma once

#include <iostream>
#include "../fmtlib.h"

class Particella{
    public:
    // =============================================
    // Costruttori
    // =============================================
    Particella();
    Particella(double massa,double carica);

    ~Particella();

    // =============================================
    // Methods
    // =============================================
    double GetMassa() const{return m_massa;}
    double GetCarica() const{return m_carica;}
    virtual void Print() const;

    protected:
    double m_massa;
    double m_carica;
};