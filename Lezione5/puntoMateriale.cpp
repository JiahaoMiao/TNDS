#include "puntoMateriale.h"


PuntoMateriale::PuntoMateriale(double massa,double carica,const Posizione & r)
:Particella{massa,carica},Posizione{r}{}
PuntoMateriale::PuntoMateriale(double massa,double carica,double x,double y,double z)
:Particella{massa,carica},Posizione{x,y,z}{}

PuntoMateriale::~PuntoMateriale(){}

CampoVettoriale PuntoMateriale::CampoElettrico(const Posizione& r) const{
    double k = this->GetCarica()/(4*pi*epsilon0);
    double Ex = k*(r.getX()-this->getX())/pow(r.Distanza(this->getX(),this->getY(),this->getZ()),3);
    double Ey = k*(r.getY()-this->getY())/pow(r.Distanza(this->getX(),this->getY(),this->getZ()),3);
    double Ez = k*(r.getZ()-this->getZ())/pow(r.Distanza(this->getX(),this->getY(),this->getZ()),3);
    return CampoVettoriale(r,Ex,Ey,Ez);
}
CampoVettoriale PuntoMateriale::CampoGravitazionale(const Posizione & r) const{
    double k = G*this->GetMassa();
    double Ex = k*(r.getX()-this->getX())/pow(r.Distanza(this->getX(),this->getY(),this->getZ()),3);
    double Ey = k*(r.getY()-this->getY())/pow(r.Distanza(this->getX(),this->getY(),this->getZ()),3);
    double Ez = k*(r.getZ()-this->getZ())/pow(r.Distanza(this->getX(),this->getY(),this->getZ()),3);
    return CampoVettoriale(r,Ex,Ey,Ez);
}