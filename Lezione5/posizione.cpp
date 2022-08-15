#include "posizione.h"

// =============================================
// Costruttori
// =============================================
Posizione::Posizione() 
:m_x{},m_y{},m_z{} {}

Posizione::Posizione(double x,double y,double z)
:m_x{x},m_y{y},m_z{z} {}

Posizione::~Posizione(){}

// =============================================
// Methods
// =============================================
//Coordinate cartesiane
double Posizione::getX() const{return m_x;}
double Posizione::getY() const{return m_y;}
double Posizione::getZ() const{return m_z;}
//Coordinate Sferiche
double Posizione::getR() const{return sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));}
double Posizione::getPhi() const{ return atan2(m_y,m_x);}
double Posizione::getTheta() const{return acos(m_z/getR());}
double Posizione::getRho() const{return sqrt(m_x*m_x+m_y*m_y);}
double Posizione::Distanza(const Posizione& r) const{
    return sqrt(pow(getX()-r.getX(),2)+
                pow(getY()-r.getY(),2)+
                pow(getZ()-r.getZ(),2));
}

double Posizione::Distanza(double x,double y,double z) const{
    return sqrt(pow(getX()-x,2)+
                pow(getY()-y,2)+
                pow(getZ()-z,2));
}

void Posizione::Print(const Posizione& r) const{
    fmt::print("Posizione: ({},{},{})\n",r.m_x,r.m_y,r.m_z);
}
