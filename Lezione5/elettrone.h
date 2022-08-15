#pragma once

#include "particella.h"
#include "../fmtlib.h"

class Elettrone: public Particella{
    public:
    Elettrone() :Particella{9.1093826e-31,-1.60217653e-19}{}
    ~Elettrone() {}

    virtual void Print() const{
        fmt::print("Elettrone: m = {},q = {}",m_massa,m_carica);
    }
};