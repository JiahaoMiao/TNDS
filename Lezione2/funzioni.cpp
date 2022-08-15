#include "funzioni.h"

Vettore Read(int n,const char* filename){
    std::ifstream fin(filename);
    Vettore v(n);

    if(!fin){
        std::cerr << "Non riesco ad aprire il file " << filename <<'\n';
        exit(1);
    }else{
        for(int i=0;i<n;i++){
            fin >> v[i];
            if(fin.eof()){
                std::cerr << "Raggiunta la fine del file prima di aver letto " << n << " dati, esco\n";
                exit(1);
            } 
        }
    }
    fin.close();
    return v;
}

double CalcolaMedia(const Vettore& v){
    double accumulo=0;
    if(v.GetN()==0) return accumulo;
    //for(size_t k=0;k<v.GetN();k++) accumulo+=v.GetComponent(k);
    for(size_t i=0;i<v.GetN();i++){
        accumulo= static_cast<double>(i)/static_cast<double>(i+1)*accumulo+
        1.0/static_cast<double>(i+1)*v.GetComponent(i);
    }
    return accumulo;
}
double CalcolaVarianza(const Vettore& v){
    double result=0;

    if(v.GetN()==0) return result;

    double old_average;
    double average=0;

    for(size_t i=0;i<v.GetN();i++){
        old_average= average;
        average= static_cast<double>(i)/static_cast<double>(i+1)*average+
            1.0/static_cast<double>(i+1)*v.GetComponent(i);

        result = 1.0/static_cast<double>(i+1)*
            (static_cast<double>(i)*result+ v.GetComponent(i)*v.GetComponent(i)+
            static_cast<double>(i)*old_average*old_average)-average*average;
    }
    return result;
}
double CalcolaMediana(Vettore v){
    double mediana =0;
    selection_sort(v);
    if(v.GetN()%2==0){
        mediana= (v[v.GetN()/2-1]+v[v.GetN()/2])/2;
    }else{
        mediana=v[v.GetN()/2];
    }
    return mediana;

}

void Print(const Vettore& v){
    for(size_t i=0;i<v.GetN();i++){
        std::cout<< v.GetComponent(i)<< '\n';
    }
}
void Print(const Vettore& v, const char* filename){
    std::ofstream fout(filename);

    for(size_t i=0;i<v.GetN();i++){
        fout << v.GetComponent(i)<< '\n';
    }
    std::cout<< "I dati del vettore sono stati scritti sul file "<< filename << "\n";

    fout.close();
}

void selection_sort(Vettore& v){
    int imin=0;
    double min=0;
    for(size_t j=0;j<v.GetN()-1;j++){
        imin=j;
        min= v[imin];
        for(size_t i=j+1;i<v.GetN();i++){
            if(v[i]< min){
                min = v[i];
                imin=i;
            }
        }
        v.Scambia(j,imin);
    }
}