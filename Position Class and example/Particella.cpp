#include "Particella.h"
 
Particella::Particella():m_massa{},m_carica{}{}
Particella::Particella(double massa,double carica):m_massa{massa},m_carica{carica}{}

Particella::Particella(const Particella & p):m_massa{p.GetMassa()},m_carica{p.GetCarica()}{}

Particella::Particella(Particella && p): m_massa{p.m_massa},m_carica{p.m_carica}{
	std::cout << "move semantic used\n";
}

Particella::~Particella(){}

//metodi
double Particella::GetMassa() const{return m_massa;}
double Particella::GetCarica() const{return m_carica;}
void Particella::setMassa(double massa){m_massa = massa;}
void Particella::setCarica(double carica){m_carica = carica;}
void Particella::Print() const{
	std::cout << "Particella: m= " << m_massa << " , q= " << m_carica << '\n';
}

Elettrone::Elettrone():Particella{9.1093837015E-31,-1.602176634E-19}{}
Elettrone::Elettrone(const Particella& p):Particella{p}{}
Elettrone::~Elettrone(){}

void Elettrone::Print() const{
	std::cout << "Elettrone: m= " << m_massa << " , q= " << m_carica << '\n';
}