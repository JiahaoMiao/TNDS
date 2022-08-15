#include "Vettore.h"

// =============================================
// constructors
// =============================================
Vettore::Vettore(){
    m_N=0;
    m_v=NULL;
    std::cout<< "Invocazione del Costruttore!\n";
}
Vettore::Vettore(size_t N){
    m_N=N;
    m_v=new double[N];
    std::cout<< "Invocazione del Costruttore!\n";
}
Vettore::Vettore(Vettore&& V){
    std::cout << "Invocazione del move constructor\n";

    m_N= V.m_N;
    m_v= V.m_v;
    V.m_N=0;
    V.m_v= nullptr;
    std::cout << "Move constructor chiamato\n";
}
Vettore::~Vettore(){
    delete []m_v;
    m_v= NULL;
    m_N=0;
    std::cout<< "Invocazione del Distruttore!\n";
}
Vettore::Vettore(const Vettore &v){
    m_N=v.m_N;
    m_v =new double[m_N];
    for(size_t i=0;i<m_N;i++){
        m_v[i] = v.GetComponent(i);
    }
}    
// =============================================
// Get methods
// =============================================
double Vettore::GetComponent(size_t i)const{
    return m_v[i];
}

// =============================================
// Set methods
// =============================================
void Vettore::SetComponent(size_t i,double a){
    m_v[i]=a;
}

// =============================================
// Methods
// =============================================
void Vettore::Scambia(size_t a,size_t b){
    double appo=m_v[a];
    m_v[a]=m_v[b];
    m_v[b]=appo;
}

double& Vettore::operator[](size_t i){
    assert((i<m_N)&&"Errore:l'indice è troppo grande");
    return m_v[i]; 
}

Vettore& Vettore::operator=(const Vettore & v){
    m_N= v.m_N;
    if(m_v){
        delete[] m_v;
    }
    m_v= new double[m_N];

    for(size_t i=0;i<m_N;i++){
        m_v[i]= v.m_v[i];
    }
    return *this;
}

Vettore& Vettore::operator=(Vettore&& V){
    std::cout<<"Invocazione del move assignement operator\n";
    delete [] m_v;

    m_N=V.m_N;
    m_v=V.m_v;

    V.m_N=0;
    V.m_v=nullptr;

    std::cout<<"Move assignment operator invocato\n";
    return *this;
}


