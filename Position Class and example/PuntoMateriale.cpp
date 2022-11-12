#include "PuntoMateriale.h"

PuntoMateriale::PuntoMateriale(const Particella& p, Position* r)
:Particella{p},m_r{r->clone()}{}
PuntoMateriale::PuntoMateriale(double massa, double carica, Position* r)
:Particella{massa,carica},m_r{r->clone()}{}
PuntoMateriale::PuntoMateriale(double massa, double carica, double x, double y, double z)
:Particella{massa,carica},m_r{new Cartesian{x,y,z}}{}
PuntoMateriale::~PuntoMateriale(){}

CampoVettoriale PuntoMateriale::CampoElettrico(Position* r) const{
	double k = GetCarica()/(4*M_PI*epsilon0*pow(m_r->Distance(r),3));
	double Ex = k*(r->getX()-m_r->getX());
	double Ey = k*(r->getY()-m_r->getY());
	double Ez = k*(r->getZ()-m_r->getZ());
	return CampoVettoriale(r,Ex,Ey,Ez);
}
CampoVettoriale PuntoMateriale::CampoGravitazionale( Position* r) const{
	double k = G*GetMassa()/pow(m_r->Distance(r),3);
	double Ex = k*(r->getX()-m_r->getX());
	double Ey = k*(r->getY()-m_r->getY());
	double Ez = k*(r->getZ()-m_r->getZ());
	return CampoVettoriale(r,Ex,Ey,Ez);
}