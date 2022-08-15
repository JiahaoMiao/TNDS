#include "posizione.h"

// =============================================
// Costruttori
// =============================================
Posizione::Posizione() 
:m_x{},m_y{},m_z{} {}

Posizione::Posizione(double x,double y,double z)
:m_x{sqrt(x*x+y*y+z*z)},m_y{atan2(y,x)} {
    if(m_x>0.) m_z=acos(z/m_x); //Theta
    else m_z=0.; 
}

Posizione::~Posizione(){}

// =============================================
// Methods
// =============================================
//Coordinate cartesiane
double Posizione::getX() const{return m_x*cos(m_y)*sin(m_z);}
double Posizione::getY() const{return m_x*sin(m_y)*sin(m_z);}
double Posizione::getZ() const{return m_x*cos(m_z);}
//Coordinate Sferiche
double Posizione::getR() const{return m_x;}
double Posizione::getPhi() const{ return m_y;}
double Posizione::getTheta() const{return m_z;}
double Posizione::getRho() const{return m_x*sin(m_z);}
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
