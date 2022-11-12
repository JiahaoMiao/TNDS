#include "Position.hpp"

//******************************************************************************
// Cartesians coordinates
//******************************************************************************

Cartesian::Cartesian():m_x{0},m_y{0},m_z{0}{}
Cartesian::Cartesian(double x,double y,double z):m_x{x},m_y{y},m_z{z}{}
Cartesian::Cartesian(Cartesian&& p):m_x{p.m_x},m_y{p.m_y},m_z{p.m_z}{}
Cartesian::Cartesian(const Cartesian& p):m_x{p.m_x},m_y{p.m_y},m_z{p.m_z}{}

Cartesian* Cartesian::clone() const{
    return new Cartesian(*this);
}

Cartesian::~Cartesian(){}

//******************************************************
// Virtual methods inherited from Position
//******************************************************

double Cartesian::getX() const{return m_x;}
double Cartesian::getY() const{return m_y;}
double Cartesian::getZ() const{return m_z;}

double Cartesian::getR() const{return sqrt(m_x*m_x+m_y*m_y+m_z*m_z);}
double Cartesian::getTheta() const{return acos(m_z/getR());}
double Cartesian::getPhi() const{return atan2(m_y,m_x);}

double Cartesian::getRho() const{return sqrt(m_x*m_x+m_y*m_y);}

double Cartesian::Distance(const Position* r) const{
    return sqrt((m_x-r->getX())*(m_x-r->getX())+(m_y-r->getY())*(m_y-r->getY())+(m_z-r->getZ())*(m_z-r->getZ()));
}

void Cartesian::Print() const    {
    std::cout << "Cartesian coordinates: (" << m_x << "," << m_y << "," << m_z << ")\n";
}

double Cartesian::Distance(double x,double y,double z) const{
    return sqrt((m_x-x)*(m_x-x)+(m_y-y)*(m_y-y)+(m_z-z)*(m_z-z));
}

//******************************************************************************
// Setters
//******************************************************************************

void Cartesian::SetX(double x){m_x=x;}
void Cartesian::SetY(double y){m_y=y;}
void Cartesian::SetZ(double z){m_z=z;}
void Cartesian::Set(double x,double y,double z){m_x=x;m_y=y;m_z=z;}

//******************************************************************************
// Spherical coordinates
//******************************************************************************
Spherical::Spherical():m_r{0},m_theta{0},m_phi{0}{}
Spherical::Spherical(double r,double theta,double phi):m_r{r},m_theta{theta},m_phi{phi}{}
Spherical::Spherical(Spherical&& p):m_r{p.m_r},m_theta{p.m_theta},m_phi{p.m_phi}{}
Spherical::Spherical(const Spherical& p):m_r{p.m_r},m_theta{p.m_theta},m_phi{p.m_phi}{}

Spherical* Spherical::clone() const{
    return new Spherical(*this);
}

Spherical::~Spherical(){}

//******************************************************
// Virtual methods inherited from Position
//******************************************************

double Spherical::getX() const{return m_r*sin(m_theta)*cos(m_phi);}
double Spherical::getY() const{return m_r*sin(m_theta)*sin(m_phi);}
double Spherical::getZ() const{return m_r*cos(m_theta);}

double Spherical::getR() const{return m_r;}
double Spherical::getTheta() const{return m_theta;}
double Spherical::getPhi() const{return m_phi;}

double Spherical::getRho() const{return m_r*sin(m_theta);}

double Spherical::Distance(const Position* p) const{
    return sqrt(m_r*m_r + pow(p->getR(),2) - 2*m_r*p->getR() * ( sin(m_theta)*sin(p->getTheta())*cos(m_phi-p->getPhi()) + cos(m_theta)*cos(p->getTheta()) ) );
}

void Spherical::Print() const    {
    std::cout << "Spherical coordinates: (" << m_r << "," << m_theta << "," << m_phi << ")\n";
}

double Spherical::Distance(double r,double theta,double phi) const{
    return sqrt(m_r*m_r + r*r - 2*m_r*r*(sin(m_theta)*sin(theta)*cos(m_phi-phi)+cos(m_theta)*cos(theta)) );
}

//******************************************************************************
// Setters
//******************************************************************************

void Spherical::SetR(double r){m_r=r;}
void Spherical::SetTheta(double theta){m_theta=theta;}
void Spherical::SetPhi(double phi){m_phi=phi;}
void Spherical::Set(double r,double theta,double phi){m_r=r;m_theta=theta;m_phi=phi;}

//******************************************************************************
// Cylindrical coordinates
//******************************************************************************

Cylindrical::Cylindrical():m_rho{0},m_phi{0},m_z{0}{}
Cylindrical::Cylindrical(double rho,double phi,double z):m_rho{rho},m_phi{phi},m_z{z}{}
Cylindrical::Cylindrical(Cylindrical&& p):m_rho{p.m_rho},m_phi{p.m_phi},m_z{p.m_z}{}
Cylindrical::Cylindrical(const Cylindrical& p):m_rho{p.m_rho},m_phi{p.m_phi},m_z{p.m_z}{}

Cylindrical* Cylindrical::clone() const{
    return new Cylindrical(*this);
}


Cylindrical::~Cylindrical(){}

//******************************************************
// Virtual methods inherited from Position
//******************************************************

double Cylindrical::getX() const{return m_rho*cos(m_phi);}
double Cylindrical::getY() const{return m_rho*sin(m_phi);}
double Cylindrical::getZ() const{return m_z;}

double Cylindrical::getR() const{return sqrt(m_rho*m_rho+m_z*m_z);}
double Cylindrical::getTheta() const{return acos(m_z/getR());}
double Cylindrical::getPhi() const{return m_phi;}
double Cylindrical::getRho() const{return m_rho;}

double Cylindrical::Distance(const Position* p) const{
    return sqrt( pow(m_rho,2) + pow(p->getRho(),2) -2*m_rho*p->getRho()*cos(m_phi-p->getPhi()) + pow((m_z-p->getZ()),2));
}

void Cylindrical::Print() const    {
    std::cout << "Cylindrical coordinates: (" << m_rho << "," << m_phi << "," << m_z << ")\n";
}

double Cylindrical::Distance(double rho,double phi,double z) const{
    return sqrt( pow(m_rho,2) + pow(rho,2) -2*m_rho*rho*cos(m_phi-phi) + pow((m_z-z),2));
}

//******************************************************************************
// Setters
//******************************************************************************

void Cylindrical::SetRho(double rho){m_rho=rho;}
void Cylindrical::SetPhi(double phi){m_phi=phi;}
void Cylindrical::SetZ(double z){m_z=z;}
void Cylindrical::Set(double rho,double phi,double z){m_rho=rho;m_phi=phi;m_z=z;}
