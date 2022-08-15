#include <algorithm> //funzioni
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector> //contenitore

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
template <typename T>
void Print(const std::vector<T>& v){
    for(size_t i{};i<v.size();i++){
        std::cout<< v[i]<< '\n';
    }
}
template <typename T>
void Print(const std::vector<T>& v, const char* filename){
    std::ofstream fout(filename);

    for(size_t i{};i<v.size();i++){
        fout << v[i]<< '\n';
    }
    std::cout<< "I dati del vector sono stati scritti sul file "<< filename << "\n";

    fout.close();
}
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