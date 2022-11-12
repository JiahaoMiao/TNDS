#pragma once

#include <iostream>
 
class Particella{
public:
//costruttori
Particella();
Particella(Particella && p);
Particella(const Particella & p);
Particella(double massa,double carica);
~Particella();

//metodi
double GetMassa() const;
double GetCarica() const;
void setMassa(double massa);
void setCarica(double carica); 
void Print() const;

protected:
double m_massa,m_carica;
};

class Elettrone: public Particella{
public:
	Elettrone();
	Elettrone(const Particella & p);
	~Elettrone();

	void Print()const;
};