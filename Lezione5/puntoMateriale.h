#pragma once

#include "particella.h"
#include "posizione.h"
#include "campoVettoriale.h"

#define pi 3.14159265358979323846
#define epsilon0 8.85418782e-12
#define G 6.67e-11

class PuntoMateriale : public Particella,Posizione{
    public:
    PuntoMateriale(double massa,double carica,const Posizione & r);
    PuntoMateriale(double massa,double carica,double x,double y,double z);

    ~PuntoMateriale();

    CampoVettoriale CampoElettrico(const Posizione& r) const;
    CampoVettoriale CampoGravitazionale(const Posizione & r) const;

};