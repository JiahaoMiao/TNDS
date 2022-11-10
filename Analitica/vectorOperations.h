#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "fmtlib.h"

// =======================================================
// somma di due vettori : somma componente per componente
// =======================================================

template <typename T>
std::vector<T> operator+(const std::vector<T> &a,const std::vector<T> &b){
    if(a.size() != b.size()){
        //throw "Trying to sum vectors with different size\n"
        std::cerr << "Trying to sum vectors with different size\n";
        exit(-1);
    }
    std::vector<T> result(a.size());
    std::transform(a.begin(),a.end(),b.begin(),result.begin(),std::plus<T>());
    //for(int i=0;i<static_cast<int>(a.size()));i++)result[i]=a[i]+b[i];
    return result;
}
// =======================================================
// somma ad a un vettore b e il risultato viene messo in a
// =======================================================

template <typename T>
std::vector<T>& operator+=(std::vector<T>& a,const std::vector<T>&b){
    if(a.size() != b.size()){
        //throw "Trying to sum vectors with different size\n"
        std::cerr << "Trying to sum vectors with different size\n";
        exit(-1);
    }
    std::transform(a.begin(),a.end(),b.begin(),a.begin(),std::plus<T>());
    //for(int i=0;i<static_cast<int>(a.size()));i++)a[i] += b[i];
    return a;
}
// =======================================================
// prodotto scalare tra due vettori
// =======================================================
template <typename T>
T operator*(const std::vector<T> &a,const std::vector<T> &b){
    if(a.size() != b.size()){
        //throw "Trying to sum vectors with different size\n"
        std::cerr << "Trying to sum vectors with different size\n";
        exit(-1);
    }
    T sum{};

    sum = inner_product(std::begin(a),std::end(a),std::begin(b),1.0);
    //for(int i=0;i<static_cast<int>(a.size());i++) sum+=a[i]*b[i];
    return sum;
}
// =======================================================
// prodotto tra scalare e un vettore
// =======================================================
template <typename T>
std::vector<T> operator*(T c, const std::vector<T> &a){
    std::vector<T> result(a.size());
    std::transform(std::begin(a),std::end(a),std::begin(result),[&c](T x){return x*c;});
    //for(int i{};i<static_cast<int>(a.size());i++) result[i]=c*a[i];
    return result;
}
// =======================================================
// prodotto tra vettore e uno scalare
// =======================================================
template <typename T>
std::vector<T> operator*(const std::vector<T> &a,T c){
    std::vector<T> result(a.size());
    std::transform(std::begin(a),std::end(a),std::begin(result),[&c](T x){return x*c;});
    //for(int i{};i<static_cast<int>(a.size());i++) result[i]=c*a[i];
    //result = c*a; //definito sopra
    return result;
}

// =======================================================
// divisione tra vettore e uno scalare
// =======================================================
template <typename T>
std::vector<T> operator/(const std::vector<T> &a,T c){
    std::vector<T> result(a.size());
    std::transform(std::begin(a),std::end(a),std::begin(result),[&c](T x){return x/c;});
    //for(int i{};i<static_cast<int>(a.size());i++) result[i]=a[i]/c;
    return result;
}

// ===========================================================
// helper function: funzioni generiche che agiscono su vettori
// ===========================================================
template <typename T>
void Print(const std::vector<T> &v){
    //fmt::print("Printing vector\n");
    fmt::print("Vector = (");
    for(auto it=v.begin();it!=v.end();it++){
        fmt::print("{},",*it);
    }
    fmt::print("\b)\n");
    //fmt::print("End of Printing vector")
}

