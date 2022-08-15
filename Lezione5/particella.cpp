#include "particella.h"


// =============================================
// Costruttori
// =============================================
Particella::Particella()
:m_massa{},m_carica{} {}
Particella::Particella(double massa,double carica)
:m_massa{massa},m_carica{carica} {}

Particella::~Particella(){
    //fmt::print("Particella Distrutta\n");
}

// =============================================
// Methods
// =============================================
void Particella::Print() const{
    fmt::print("Particella: m = {},q = {}",m_massa,m_carica);
}