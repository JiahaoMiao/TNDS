#include <iostream>
#include <cassert>

#include "posizione.h"
#include "particella.h"
#include "campoVettoriale.h"
#include "puntoMateriale.h"
#include "fmtlib.h"


bool are_close(double calculated,double expected, double epsilon =1e-7){
    return fabs(calculated-expected)<epsilon;
}

void test_coordinates(void){
    Posizione p{1,2,3};

    assert(are_close(p.getX(),1.0));
    assert(are_close(p.getY(),2.0));
    assert(are_close(p.getZ(),3.0));

    assert(are_close(p.getR(),3.7416573867739));
    assert(are_close(p.getPhi(),1.1071487177941));
    assert(are_close(p.getTheta(),0.64052231267943));

    assert(are_close(p.getRho(), 2.2360679774998));

}

void test_coulomb_law(void) {
  // 0.5 µC charge with no mass (irrelevant for the electric field)
  PuntoMateriale particella{1.0, 5e-7, 5, 3, -2, };
  Posizione p{-2, 4, 1};
  
  CampoVettoriale V{particella.CampoElettrico(p)};
  fmt::print("F_e= ({},{},{})\n",V.getFx(),V.getFy(),V.getFz());
  
  assert(are_close(V.getFx(), -69.41150052142065));
  assert(are_close(V.getFy(), 9.915928645917235));
  assert(are_close(V.getFz(), 29.747785937751708));
}

void test_newton_law(void) {
  // 10⁹ tonnes, without charge (irrelevant for the gravitational field)
  PuntoMateriale particella{1e12, 0, 5, 3, -2, };
  Posizione p{-2, 4, 1};
  
  CampoVettoriale V{particella.CampoGravitazionale(p)};

  fmt::print("F_g= ({},{},{})\n",V.getFx(),V.getFy(),V.getFz());
    
  assert(are_close(V.getFx(), -1.0302576701177));
  assert(are_close(V.getFy(), 0.14717966715968));
  assert(are_close(V.getFz(), 0.44153900147903));
}

int main(){
    test_coordinates();
    fmt::print("Test Posizione passato con successo!\n");

    test_coulomb_law();
    fmt::print("Test Coulomb passato con successo!\n");

    test_newton_law();
    fmt::print("Test Newton passato con successo!\n");

    return 0;
}