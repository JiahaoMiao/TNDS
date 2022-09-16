#pragma once

#include "randomGen.h"
#include <iostream>

class AttritoViscoso{
    public:

    AttritoViscoso(double rho,double rho_0,double x,double R,double eta,double sigmat,double sigmax,double sigmaR)
    :m_rho{rho},m_rho_0{rho_0},m_x_input{x},m_R_input{R},m_eta_input{eta},m_sigmat{sigmat},m_sigmax{sigmax},m_sigmaR{sigmaR} {
        m_random.setA(1664525);
        m_random.setB(1013904223);
        m_random.setM(1<<31);//sposta il bit nella posizione 1 alla posizione 31
    }
    
    ~AttritoViscoso(){};

    constexpr double getRho() {return m_rho;}
    constexpr double getRho0() {return m_rho_0;}
    constexpr double getX() {return m_x_input;}
    constexpr double getR() {return m_R_input;}
    constexpr double getEta() {return m_eta_input;}
    constexpr double getT() {return m_t_input;}
    constexpr double getV() {return m_v_input;}

    constexpr double getXmis() {return m_x_misurato;}
    constexpr double getRmis() {return m_R_misurato;}
    constexpr double getTmis() {return m_t_misurato;}
    constexpr double getVmis() {return m_v_misurato;}
    constexpr double getEtamis() {return m_eta_misurato;}

    //Procedura che esegue l'esperimento e prende le misure di tempo, spazio e raggio
    void Esegui(){
        //Calcolo la velocita' limite data dalla legge di Stokes
        m_v_input = 2*m_R_input*m_R_input*(m_rho-m_rho_0)*g/(9*m_eta_input);
        //Conoscendo velocita' e spazio percorso, calcolo il tempo
        m_t_input = m_x_input/m_v_input;
    
        //Genero le misure dell'esperimento
        m_t_misurato = m_random.Gauss(m_t_input,m_sigmat);
        m_x_misurato = m_random.Gauss(m_x_input,m_sigmax);
        m_R_misurato = m_random.Gauss(m_R_input,m_sigmaR);
    }
    //Procedura che analizza i dati raccolti dall'esperimento
    void Analizza(){
        //Calcolo la velocita' misurata
        m_v_misurato = m_x_misurato/m_t_misurato;
        //Calcolo il coefficiente di attrito viscoso avendo velocita',raggio e le densita'
        m_eta_misurato = 2*m_R_misurato*m_R_misurato*(m_rho-m_rho_0)*g/(9*m_v_misurato);
    }

    private:
    //Parametri dell'esperimento
    double m_rho{},m_rho_0{},m_x_input{},m_R_input{},m_eta_input{};
    const double g{9.81};
    //Generatore di numeri pseudo-randomici
    RandomGen m_random{1};
    
    //Valori delle quantita' misurabili
    //input    : valori assunti come ipotesi nella simulazione
    //misurato : valore dopo la simulazione di misura
    double m_t_input, m_t_misurato,m_sigmat;
    double m_x_misurato,m_sigmax;
    double m_R_misurato,m_sigmaR;
    double m_eta_misurato;
    double m_v_input,m_v_misurato;
};