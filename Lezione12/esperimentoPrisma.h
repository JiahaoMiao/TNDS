#pragma once

#include "randomGen.h"
#include <iostream>

class EsperimentoPrisma{

public:
    EsperimentoPrisma(double A,double B,double alpha,double lambda_1,double lambda_2,double sigma,double theta_0)
    :m_lambda1{lambda_1},m_lambda2{lambda_2},m_alpha{alpha},m_sigma{sigma},m_A_input{A},m_B_input{B},m_th0_input{theta_0}{
    m_random.setA(1664525);
    m_random.setB(1013904223);
    m_random.setM(1<<31);//sposta il bit nella posizione 1 alla posizione 31
    }

    ~EsperimentoPrisma(){}
    constexpr double getA() {return m_A_input;}
    constexpr double getB() {return m_B_input;}
    constexpr double getTh0() {return m_th0_input;}
    constexpr double getTh1() {return m_th1_input;}
    constexpr double getTh2() {return m_th2_input;}
    constexpr double getN1() {return m_n1_input;}
    constexpr double getN2() {return m_n2_input;}
    constexpr double getDm1() {return m_dm1_input;}
    constexpr double getDm2() {return m_dm2_input;}

    constexpr double getAmis() {return m_A_misurato;}
    constexpr double getBmis() {return m_B_misurato;}
    constexpr double getTh0mis() {return m_th0_misurato;}
    constexpr double getTh1mis() {return m_th1_misurato;}
    constexpr double getTh2mis() {return m_th2_misurato;}
    constexpr double getN1mis() {return m_n1_misurato;}
    constexpr double getN2mis() {return m_n2_misurato;}
    constexpr double getDm1mis() {return m_dm1_misurato;}
    constexpr double getDm2mis() {return m_dm2_misurato;}

    void setA(double A){m_A_input = A;}
    void setB(double B){m_B_input = B;}
    void setAlpha(double Alpha){m_alpha = Alpha;}
    void setSigma(double sigma){m_sigma =sigma;}
    void setLambda_1(double lambda1){m_lambda1 =lambda1;}
    void setLambda_2(double lambda2){m_lambda2 =lambda2;}
    void setTheta0(double theta_0){m_th0_input = theta_0;}


    void Esergui(){
        //Indici di rifrazione
        m_n1_input = sqrt(m_A_input+m_B_input/(m_lambda1*m_lambda1));
        m_n2_input = sqrt(m_A_input+m_B_input/(m_lambda2*m_lambda2));

        //Deviazione
        m_dm1_input = 2.*asin(m_n1_input*sin(0.5*m_alpha))-m_alpha;
        m_dm2_input = 2.*asin(m_n2_input*sin(0.5*m_alpha))-m_alpha;
        
        //Angoli di deviazione minima
        m_th1_input =m_th0_input + m_dm1_input;//Calcolo i valori "veri"
        m_th2_input=m_th0_input + m_dm2_input;//Calcolo i valori "veri"

        //"Sporco" i valori veri con una incertezza
        m_th0_misurato = m_random.Gauss(m_th0_input,m_sigma);
        m_th1_misurato = m_random.Gauss(m_th1_input,m_sigma);
        m_th2_misurato = m_random.Gauss(m_th2_input,m_sigma);
    }
    
    void Analizza(){
        //Deviazione misurata
        m_dm1_misurato = m_th1_misurato - m_th0_misurato;
        m_dm2_misurato = m_th2_misurato - m_th0_misurato;

        //Indici di Rifrazione misurati
        m_n1_misurato = sin(0.5*(m_dm1_misurato+m_alpha))/sin(m_alpha/2);
        m_n2_misurato = sin(0.5*(m_dm2_misurato+m_alpha))/sin(m_alpha/2);

        //Finalmente calcolo i coefficienti di Cauchy
        m_A_misurato = (pow(m_lambda2*m_n2_misurato,2)-pow(m_lambda1*m_n1_misurato,2))/(pow(m_lambda2,2)-pow(m_lambda1,2));
        m_B_misurato = (pow(m_n2_misurato,2)-pow(m_n1_misurato,2))/(pow(m_lambda2,-2)-pow(m_lambda1,-2));

    }

private:

double m_lambda1,m_lambda2,m_alpha,m_sigma;

//generatore di numeri casuali
RandomGen m_random{1};
//Valori delle quantita' misurabili
//input    : valori assunti come ipotesi nella simulazione
//misurato : valore dopo la simulazione di misura

double m_A_input, m_A_misurato;
double m_B_input, m_B_misurato;
double m_n1_input, m_n1_misurato;
double m_n2_input, m_n2_misurato;
double m_dm1_input, m_dm1_misurato;
double m_dm2_input, m_dm2_misurato;
double m_th0_input, m_th0_misurato;
double m_th1_input, m_th1_misurato;
double m_th2_input, m_th2_misurato;

};