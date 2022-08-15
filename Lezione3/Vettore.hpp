#pragma once

#include <iostream>
#include <cassert>

template <typename T>
class Vettore{
    public:
    // =============================================
    // constructors
    // =============================================
    Vettore(){
    m_N=0;
    m_v=NULL;
    std::cout<< "Invocazione del Costruttore!\n";
    }
    Vettore(size_t N){
    m_N=N;
    m_v=new T[N];
    std::cout<< "Invocazione del Costruttore!\n";
    }
    Vettore(const Vettore & v){//Copy constructor
     m_N=v.m_N;
    m_v =new T[m_N];
    for(size_t i=0;i<m_N;i++){
        m_v[i] = v.GetComponent(i);
    }
    }    

    Vettore(Vettore&& V){//move constructor
    std::cout << "Invocazione del move constructor\n";

    m_N= V.m_N;
    m_v= V.m_v;
    V.m_N=0;
    V.m_v= nullptr;
    std::cout << "Move constructor chiamato\n";
    }
    ~Vettore(){
    delete []m_v;
    m_v= NULL;
    m_N=0;
    std::cout<< "Invocazione del Distruttore!\n";
    }

    // =============================================
    // Get methods
    // =============================================
    size_t GetN() const{
    return m_N;
    }
    T GetComponent(size_t i)const{
    return m_v[i];
    }

    // =============================================
    // Set methods
    // =============================================
    void SetComponent(size_t i,T a){
    m_v[i]=a;
    }

    // =============================================
    // Methods
    // =============================================
    void Scambia(size_t a,size_t b){
    T appo=m_v[a];
    m_v[a]=m_v[b];
    m_v[b]=appo;
    }
    T& operator[](size_t i){
    assert((i<m_N)&&"Errore:l'indice è troppo grande");
    return m_v[i]; 
    }
    Vettore& operator=(const Vettore & v){//Operatore di assegnazione
    m_N= v.m_N;
    if(m_v){
        delete[] m_v;
    }
    m_v= new T[m_N];

    for(size_t i=0;i<m_N;i++){
        m_v[i]= v.m_v[i];
    }
    return *this;
    }
    Vettore& operator=(Vettore&& V){ //move assignment operator
     std::cout<<"Invocazione del move assignement operator\n";
    delete [] m_v;

    m_N=V.m_N;
    m_v=V.m_v;

    V.m_N=0;
    V.m_v=nullptr;

    std::cout<<"Move assignment operator invocato\n";
    return *this;
    }

    private:
    size_t m_N;
    T* m_v;
};