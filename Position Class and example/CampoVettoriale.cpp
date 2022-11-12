#include "CampoVettoriale.h"

CampoVettoriale::CampoVettoriale(Position* p):m_r{p->clone()},m_Fx{},m_Fy{},m_Fz{}{}
CampoVettoriale::CampoVettoriale(Position* p, double Fx, double Fy, double Fz):m_r{p->clone()},m_Fx{Fx},m_Fy{Fy},m_Fz{Fz}{}
CampoVettoriale::CampoVettoriale(double x, double y, double z, double Fx, double Fy, double Fz):m_r{new Cartesian{x,y,z}},m_Fx{Fx},m_Fy{Fy},m_Fz{Fz}{}
CampoVettoriale::~CampoVettoriale(){}

  CampoVettoriale & CampoVettoriale::operator+=( const CampoVettoriale & v){
		return (*this)= (*this)+v;
	}
  CampoVettoriale CampoVettoriale::operator+( const CampoVettoriale & v) const{
		CampoVettoriale sum(v);
		sum.m_Fx += getFx();
		sum.m_Fy += getFy(); 
		sum.m_Fz += getFz();
		return sum;
	}

  double CampoVettoriale::Modulo(){
		return sqrt(m_Fx*m_Fx+m_Fx*m_Fx+m_Fz*m_Fz);
	}