#include "campoVettoriale.h"

CampoVettoriale::CampoVettoriale(const Posizione & r)
: Posizione{r},m_Fx{},m_Fy{},m_Fz{} {}

CampoVettoriale::CampoVettoriale(const Posizione & r,double Fx,double Fy,double Fz)
: Posizione{r},m_Fx{Fx},m_Fy{Fy},m_Fz{Fz} {}
CampoVettoriale::CampoVettoriale(double x,double y,double z,double Fx,double Fy,double Fz)
: Posizione{x,y,z},m_Fx{Fx},m_Fy{Fy},m_Fz{Fz} {}

CampoVettoriale::~CampoVettoriale(){}

CampoVettoriale CampoVettoriale::operator+(const CampoVettoriale & v) const{
    return CampoVettoriale{getX(),getY(),getZ(),
                           getFx()+v.getFx(),
                           getFy()+v.getFy(),
                           getFz()+v.getFz()};
}

CampoVettoriale& CampoVettoriale::operator+=(const CampoVettoriale & w){
    return (*this) = (*this) + w;
}   // v+=w dove this è il puntatore che punta v 

double CampoVettoriale::Modulo() const{
    return sqrt(m_Fx*m_Fx+m_Fy*m_Fy+m_Fz*m_Fz);
}