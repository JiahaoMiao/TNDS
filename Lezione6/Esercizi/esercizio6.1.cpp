#include <cassert>
#include <cmath>

#include "solutore.h"
#include "fmtlib.h"

bool are_close(double calculated,double expected, double epsilon =1e-7){
    return fabs(calculated-expected)<epsilon;
}

void test_zeroes(){
    //Bisezione s{};
    //Secante s{}; 
    Newton s{};
    Parabola f(3,5,-2);
    s.SetPrecisione(1e-8);

    double appo{};
    
    appo= s.CercaZeri(-3.0,-1.0,f,1e-7);   
    fmt::print("x0 = {0:.{1}f} {2} \n",appo,12,s.GetNiterations()); 
    assert( are_close(appo,-2.0) );//Zero in mezzo ad [a,b]
    
    appo= s.CercaZeri(-2.0,0.0,f,1e-7);
    fmt::print("x0 = {0:.{1}f} {2} \n",appo,12,s.GetNiterations()); 
    assert( are_close(appo,-2.0) );//Zero in estremo a
    
    appo= s.CercaZeri(-4.0,-2.0,f,1e-7);
    fmt::print("x0 = {0:.{1}f} {2} \n",appo,12,s.GetNiterations()); 
    assert( are_close(appo,-2.0) );//Zero in estremo b
    
    appo= s.CercaZeri(1e-15,2./3.,f,1e-7); // 1e-15 è il massimo con cui lavora, 1e-16 è 0 per il calcolatore
    fmt::print("x0 = {0:.{1}f} {2} \n",appo,12,s.GetNiterations()); 
    assert( are_close(appo,1.0/3) );//Altro zero
}

void test_derivata(){
    Parabola p(3,5,-2);
    Seno s{3,-5,2};

    double h= 1e-3;

    double appo{};
    
    appo= derivata(p,-1,h);
    fmt::print("f'(-1) = {0:.{1}f} \n",appo,12); 
    assert( are_close(appo,-1.0) ); //Risultato intero

    appo= derivata(p,-5./6.,h);
    fmt::print("f'(-5/6) = {0:.{1}f} \n",appo,12); 
    assert( are_close(appo,0.0) ); //Risultato 0

    appo= derivata(p,-1./18.,h);
    fmt::print("f'(-1/18) = {0:.{1}f} \n",appo,12); 
    assert( are_close(appo,14./3.) ); //Risultato periodico

    appo= derivata(s,2./5.,h);
    fmt::print("f'(2/5) = {0:.{1}f} \n",appo,12);  
    assert( are_close(appo,-15.0) ); //Risultato intero
    

    appo= derivata(s,1.,h);
    fmt::print("f'(1) = {0:.{1}f} \n",appo,12); 
    assert( are_close(appo,-15.0*cos(-5*1+2)) ); //Risultato intero

    appo= derivata(s,M_PI,h);
    fmt::print("f'(Pi) = {0:.{1}f} \n",appo,12); 
    assert( are_close(appo,-15.0*cos(-5*M_PI+2)) ); //Risultato intero


}


int main (){

    test_zeroes();

    fmt::print("Test Bisezione passato!\n");

    //test_derivata();

    //fmt::print("Test derivata passato!\n");


    return 0;
}