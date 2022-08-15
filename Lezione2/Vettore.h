#pragma once

#include <iostream>
#include <cassert>

class Vettore{
    public:
    // =============================================
    // constructors
    // =============================================
    Vettore();
    Vettore(size_t N);
    Vettore(const Vettore &); //Copy constructor
    Vettore(Vettore&& V); //move constructor
    ~Vettore();

    // =============================================
    // Get methods
    // =============================================
    size_t GetN() const{
    return m_N;
    }
    double GetComponent(size_t)const;

    // =============================================
    // Set methods
    // =============================================
    void SetComponent(size_t,double);

    // =============================================
    // Methods
    // =============================================
    void Scambia(size_t,size_t);
    double& operator[](size_t);
    Vettore& operator=(const Vettore &);//Operatore di assegnazione
    
    Vettore& operator=(Vettore&& V); //move assignment operator


    private:
    size_t m_N;
    double* m_v;
};