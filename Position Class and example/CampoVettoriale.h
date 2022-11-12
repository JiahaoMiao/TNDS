#ifndef __CampoVettoriale_h__
#define __CampoVettoriale_h__

#include <cmath>
#include "Position.hpp"

class CampoVettoriale {

public:

  CampoVettoriale( Position* p);
  CampoVettoriale( Position* p, double Fx, double Fy, double Fz);
	//Cartesiano
  CampoVettoriale(double x, double y, double z, double Fx, double Fy, double Fz);
  ~CampoVettoriale();

  CampoVettoriale & operator+=( const CampoVettoriale & ) ;
  CampoVettoriale operator+( const CampoVettoriale & ) const;
  
  double getFx() const {return m_Fx;}
  double getFy() const {return m_Fy;}
  double getFz() const {return m_Fz;}

  double Modulo();

private:
  Position * m_r;
  double m_Fx, m_Fy, m_Fz;
	
};

#endif // __CampoVettoriale_h__ 
