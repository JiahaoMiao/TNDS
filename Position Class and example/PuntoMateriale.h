#ifndef __PuntoMateriale_h__
#define __PuntoMateriale_h__

#include "Particella.h"
#include "Position.hpp"

#include "CampoVettoriale.h"



class PuntoMateriale : public Particella {

public:
	PuntoMateriale(const Particella&, Position*);
  PuntoMateriale(double massa, double carica, Position*);
  PuntoMateriale(double massa, double carica, double x, double y, double z);
  ~PuntoMateriale();

	Position * getPosition(){return m_r;}

  CampoVettoriale CampoElettrico( Position*) const ;
  CampoVettoriale CampoGravitazionale( Position*) const;

const double epsilon0{8.85418782e-12};
const double  G{6.67e-11};

private:

Position * m_r;
};

#endif // __PuntoMateriale_h__