#pragma once

#include <cmath>

/*Classe astratta, non è possibile creare 
oggetti di questa classe, ogni classe figlia
deve implementare(ovveride) le funzioni virtual
di questa classe, altrimenti si incorre in un errore 
di compilazione */

class FunzioneBase{
    public:

    virtual double Eval(double x) const=0;
    virtual ~FunzioneBase(){;};
};

class Retta:public FunzioneBase{
    public:
    // ==================================
    // constructors
    // ==================================
    Retta():m_m{1.},m_q{}{}
    Retta(double m,double q)
    :m_m{m},m_q{q}{};

    virtual ~Retta(){;};
    virtual double Eval(double x) const override{
        return m_m * x + m_q;
    }

    // ==================================
    // Set&Get Methods
    // ==================================
    void SetM(double m){m_m=m;};
    double GetM() const {return m_m;};
    void SetQ(double q){m_q=q;};
    double GetQ() const {return m_q;};

    private:
    double m_m,m_q;
};

class Parabola:public FunzioneBase{
    public:
    // ==================================
    // constructors
    // ==================================
    Parabola():m_a{},m_b{},m_c{1.}{};
    Parabola(double a,double b,double c)
    :m_a{a},m_b{b},m_c{c}{};

    virtual ~Parabola(){;};
    virtual double Eval(double x) const override{
        return (m_a * x + m_b) * x + m_c;
    }

    // ==================================
    // Set&Get Methods
    // ==================================
    void SetA(double a){m_a=a;};
    double GetA() const {return m_a;};
    void SetB(double b){m_b=b;};
    double GetB() const {return m_b;};
    void SetC(double c){m_c=c;};
    double GetC() const {return m_c;};
    

    private:
    double m_a,m_b,m_c;
};

class Coseno:public FunzioneBase{
    public:
    // ==================================
    // constructors
    // ==================================
    Coseno():m_a{1.},m_b{1.},m_c{}{};
    Coseno(double a,double b,double c)
    :m_a{a},m_b{b},m_c{c}{};

    virtual double Eval(double x) const override {
        return m_a*cos(m_b*x+m_c);
    }

    // ==================================
    // Set&Get Methods
    // ==================================
    void SetA(double a){m_a=a;};
    double GetA() const {return m_a;};
    void SetB(double b){m_b=b;};
    double GetB() const {return m_b;};
    void SetC(double c){m_c=c;};
    double GetC() const {return m_c;};

    private:
    double m_a,m_b,m_c;
};

class Seno:public FunzioneBase{
    public:
    // ==================================
    // constructors
    // ==================================
    Seno():m_a{},m_b{1.},m_c{}{};
    Seno(double a,double b,double c)
    :m_a{a},m_b{b},m_c{c}{};

    virtual double Eval(double x) const override {
        return m_a*sin(m_b*x+m_c);
    }

    // ==================================
    // Set&Get Methods
    // ==================================
    void SetA(double a){m_a=a;};
    double GetA() const {return m_a;};
    void SetB(double b){m_b=b;};
    double GetB() const {return m_b;};
    void SetC(double c){m_c=c;};
    double GetC() const {return m_c;};

    private:
    double m_a,m_b,m_c;
};