#pragma once

#include <iostream>
#include <cmath>

#include "../fmtlib.h"

class Posizione{
    public:
    // =============================================
    // Costruttori
    // =============================================
    Posizione();
    Posizione(double x,double y,double z);

    ~Posizione();

    // =============================================
    // Methods
    // =============================================
    //Coordinate cartesiane
    double getX() const;
    double getY() const;
    double getZ() const;
    //Coordinate Sferiche
    double getR() const;
    double getPhi() const;
    double getTheta() const;
    double getRho() const;//Raggio delle coordinate cilindriche
    double Distanza(const Posizione& r) const; // Distanza da un altro punto
    double Distanza(double x,double y,double z) const; // Distanza da un altro punto
    virtual void Print(const Posizione& r) const;

    private:
    double m_x,m_y,m_z;
};
