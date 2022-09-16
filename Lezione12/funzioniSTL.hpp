#include <algorithm> //funzioni
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector> //contenitore


// ==============================================================
// Questa funzione carica su un vector<T> n dati letti da un file
// ==============================================================
template <typename T>
std::vector<T> Read(int n,const char* filename){
    std::ifstream fin{filename};
    std::vector<T> v;

    if(!fin){
        std::cerr << "Non riesco ad aprire il file " << filename <<'\n';
        exit(1);
    }else{
        for(int i{};i<n;i++){
            T val{};
            fin >> val;
            v.push_back(val);
            if(fin.eof()){
                std::cerr << "Raggiunta la fine del file prima di aver letto " << n << " dati, esco\n";
                exit(1);
            } 
        }
    }
    fin.close();
    return v;
}

// =======================================================
// Questa funzione calcola la Media dato un vector di dati
// =======================================================
template <typename T>
T CalcolaMedia(const std::vector<T>& v){
    T accumulo{};
    if(v.size()==0) return accumulo;
    //for(size_t k=0;k<v.size();k++) accumulo+=v.GetComponent(k);
    for(size_t i{};i<v.size();i++){
        accumulo= static_cast<double>(i)/static_cast<double>(i+1)*accumulo+
        1.0/static_cast<double>(i+1)*v[i];
    }
    return accumulo;
}

// ========================================================================================================
// Questa funzione calcola la Media dato un vector di dati e gli indici di dove inizia e termina il calcolo
// ========================================================================================================
template <typename T>
T CalcolaMedia(const std::vector<T>& v,unsigned int begin,unsigned int end){
    if(end>v.size()){
        std::cerr << "Stai sommando più elementi di quelli che hai!\n";
        exit(1);
    }
    T accumulo{};
    if(v.size()==0) return accumulo;
    //for(size_t k=0;k<v.size();k++) accumulo+=v.GetComponent(k);
    for(unsigned int i{begin};i<end;i++){
        accumulo= static_cast<double>(i)/static_cast<double>(i+1)*accumulo+
        1.0/static_cast<double>(i+1)*v[i];
    }
    return accumulo;
}

// ==========================================================
// Questa funzione calcola la Varianza dato un vector di dati
// ==========================================================
template <typename T>
T CalcolaVarianza(const std::vector<T>& v){
    T result{};

    if(v.size()==0) return result;

    T old_average;
    T average{};

    for(size_t i{};i<v.size();i++){
        old_average= average;
        average= static_cast<double>(i)/static_cast<double>(i+1)*average+
            1.0/static_cast<double>(i+1)*v[i];

        result = 1.0/static_cast<double>(i+1)*
            (static_cast<double>(i)*result+ v[i]*v[i]+
            static_cast<double>(i)*old_average*old_average)-average*average;
    }
    return result;
}
// ===========================================================================================================
// Questa funzione calcola la Varianza dato un vector di dati e gli indici di dove inizia e termina il calcolo
// ===========================================================================================================
template <typename T>
T CalcolaVarianza(const std::vector<T>& v,unsigned int begin,unsigned int end){
    if(end>v.size()){
        std::cerr << "Stai sommando più elementi di quelli che hai!\n";
        exit(1);
    }
    T result{};

    if(v.size()==0) return result;

    T old_average;
    T average{};

    for(size_t i{begin};i<end;i++){
        old_average= average;
        average= static_cast<double>(i)/static_cast<double>(i+1)*average+
            1.0/static_cast<double>(i+1)*v[i];

        result = 1.0/static_cast<double>(i+1)*
            (static_cast<double>(i)*result+ v[i]*v[i]+
            static_cast<double>(i)*old_average*old_average)-average*average;
    }
    return result;
}
// =============================================================================
// Questa funzione calcola la Mediana dato un vector di dati(Riordina il vector)
// =============================================================================
template <typename T>
T CalcolaMediana(std::vector<T> v){
    T mediana {};
    sort(v.begin(),v.end());
    if(v.size()%2==0){
        mediana= (v[v.size()/2-1]+v[v.size()/2])/2;
    }else{
        mediana=v[v.size()/2];
    }
    return mediana;

}
// ======================================================
// Questa procedura stampa gli elementi di vector a video
// ======================================================
template <typename T>
void Print(const std::vector<T>& v){
    for(size_t i{};i<v.size();i++){
        std::cout<< v[i]<< '\n';
    }
}
// =========================================================
// Questa procedura stampa gli elementi di vector su un file
// =========================================================
template <typename T>
void Print(const std::vector<T>& v, const char* filename){
    std::ofstream fout(filename);

    for(size_t i{};i<v.size();i++){
        fout << v[i]<< '\n';
    }
    std::cout<< "I dati del vector sono stati scritti sul file "<< filename << "\n";

    fout.close();
}

// ============================================================================
// Questa funzione fa la regressione lineare data due vector ascisse e ordinate
// ============================================================================
template <typename T>
void linReg(std::vector<T> x,std::vector<T> y,T * m, T * q){

  T ybar, xbar; //Baricentro
  T accusotto{};
  T accusopra{};

  xbar = Media(x.begin(),x.end());
  ybar = Media(y.begin(),y.end());
  
  for(size_t i=0; i< x.size(); i++){
    accusotto += pow(x[i]-xbar,2);
    accusopra += (x[i]-xbar)*(y[i]-ybar);
  }
  *m = accusopra/accusotto;
  *q = ybar - (*m)*xbar;
}

// ============================================================================
// Questa funzione fa la regressione lineare data due vector ascisse e ordinate
// ============================================================================
template <typename T>
void linRegPes(std::vector<T> x,std::vector<T> y, std::vector<T> err_y,T * m, T * q){

  if(x.size()!=y.size() || x.size() != err_y.size() || y.size()!= err_y.size()){
    std::cerr << "Controlla che i dati nel file siano corretti\n"; 
  }
 
  std::vector<T> w{}; //Dichiaro il vettore dei pesi

  for(size_t i=0; i < err_y.size(); i++){
    w.push_back(pow(err_y[i],-2));    
  }

  T S_wx{},S_wy{},S_wxy{},S_w{},S_wx2{};

  for(size_t i{}; i< x.size(); i++){
    S_wx += w[i]*x[i];
    S_wy += w[i]*y[i];
    S_wxy += w[i]*x[i]*y[i];
    S_w += w[i];
    S_wx2 += w[i]*x[i]*x[i];
  }

  T msopra = S_w*S_wxy-S_wx*S_wy;
  T qsopra = S_wx2*S_wy-S_wx*S_wxy;
  T Delta = S_w*S_wx2-pow(S_wx,2);
  
  *m = msopra/Delta;
  *q = qsopra/Delta;
}


// ============================================================================
// Questa funzione calcola il coefficiente di correlazione passo per passo
// ============================================================================


/*template <typename T>
void selection_sort(std::vector<T>& v){
    int imin{};
    T min{};
    for(size_t j{};j<v.size()-1;j++){
        imin=j;
        min= v[imin];
        for(size_t i=j+1;i<v.size();i++){
            if(v[i]< min){
                min = v[i];
                imin=i;
            }
        }
        v.swap(j,imin);
    }
}*/