#pragma once

#include <iostream>
#include <fstream>
#include "Vettore.hpp"
template <typename T>
Vettore<T> Read(int,const char*);
template <typename T>
T CalcolaMedia(const Vettore<T>&);
template <typename T>
T CalcolaVarianza(const Vettore<T>&);
template <typename T>
T CalcolaMediana(Vettore<T>);

template <typename T>
void Print(const Vettore<T>&);
template <typename T>
void Print(const Vettore<T>&, const char*);

template <typename T>
void selection_sort(Vettore<T>&);

template <typename T>
Vettore<T> Read(int n,const char* filename){
    std::ifstream fin{filename};
    Vettore<T> v{n};

    if(!fin){
        std::cerr << "Non riesco ad aprire il file " << filename <<'\n';
        exit(1);
    }else{
        for(size_t i{};i<n;i++){
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
template <typename T>
T CalcolaMedia(const Vettore<T>& v){
    T accumulo{};
    if(v.GetN()==0) return accumulo;
    //for(size_t k=0;k<v.GetN();k++) accumulo+=v.GetComponent(k);
    for(size_t i{};i<v.GetN();i++){
        accumulo= static_cast<double>(i)/static_cast<double>(i+1)*accumulo+
        1.0/static_cast<double>(i+1)*v.GetComponent(i);
    }
    return accumulo;
}
template <typename T>
T CalcolaVarianza(const Vettore<T>& v){
    T result{};

    if(v.GetN()==0) return result;

    T old_average;
    T average{};

    for(size_t i{};i<v.GetN();i++){
        old_average= average;
        average= static_cast<double>(i)/static_cast<double>(i+1)*average+
            1.0/static_cast<double>(i+1)*v.GetComponent(i);

        result = 1.0/static_cast<double>(i+1)*
            (static_cast<double>(i)*result+ v.GetComponent(i)*v.GetComponent(i)+
            static_cast<double>(i)*old_average*old_average)-average*average;
    }
    return result;
}
template <typename T>
T CalcolaMediana(Vettore<T> v){
    T mediana {};
    selection_sort(v);
    if(v.GetN()%2==0){
        mediana= (v[v.GetN()/2-1]+v[v.GetN()/2])/2;
    }else{
        mediana=v[v.GetN()/2];
    }
    return mediana;

}
template <typename T>
void Print(const Vettore<T>& v){
    for(size_t i{};i<v.GetN();i++){
        std::cout<< v.GetComponent(i)<< '\n';
    }
}
template <typename T>
void Print(const Vettore<T>& v, const char* filename){
    std::ofstream fout(filename);

    for(size_t i{};i<v.GetN();i++){
        fout << v.GetComponent(i)<< '\n';
    }
    std::cout<< "I dati del vettore sono stati scritti sul file "<< filename << "\n";

    fout.close();
}
template <typename T>
void selection_sort(Vettore<T>& v){
    int imin{};
    T min{};
    for(size_t j{};j<v.GetN()-1;j++){
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