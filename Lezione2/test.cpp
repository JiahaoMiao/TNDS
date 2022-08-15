#include "Vettore.h"
#include <iostream>

int main(){
    //Costruttore senza argomenti
    Vettore vnull;
    std::cout <<"Vettore vnull: dimensione = " << vnull.GetN() <<"\n";
    //Costruttore con intero
    Vettore v(10);
    std::cout <<"Vettore v: dimensione = " << v.GetN() <<"\n";
    
    for(size_t k=0;k<v.GetN();k++){
        std::cout << v.GetComponent(k) << " ";
    }
    std::cout << "\n";
    //Cambio il contenuto di v
    for(size_t k=0;k<v.GetN();k++){
        v.SetComponent(k,k+2);
    }
    std::cout << "Vettore v (dopo le modifiche): dimensione = " << v.GetN()<<"\n";

    for(size_t k=0;k<v.GetN();k++){
        std::cout << v.GetComponent(k) << " ";
    }
    std::cout << "\n";
    //Uso il copy constructor per costruire w
    Vettore w(v); //equivalente a Vettore w = v;

    std::cout << "Vettore w: dimensione = " << w.GetN() << "\n";
    for(size_t k=0;k<w.GetN();k++){
        std::cout << w.GetComponent(k) << " ";
    }
    std::cout << "\n";

    std::cout<< "Cambio una componente di v"<< std::endl;
    v.SetComponent(4,99);

    std::cout << "Vettore v: dimensione = " << v.GetN() << "\n";
    for(size_t k=0;k<v.GetN();k++){
        std::cout << v.GetComponent(k) << " ";
    }
    std::cout << "\n";

    std::cout << "Vettore w: dimensione = " << w.GetN() << "\n";
    for(size_t k=0;k<w.GetN();k++){
        std::cout << w.GetComponent(k) << " ";
    }
    std::cout << "\n";

    //Operatore di assegnazione
    Vettore z(10);
    z = w;
    
    return 0;
}