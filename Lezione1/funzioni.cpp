#include "funzioni.h"


double* ReadDataFromFile(const char filename[], int*size){
    //int conta;
    //double appo;
    double *data;
    std::ifstream file_in;

    file_in.open(filename);
    /*
    if(!file_in){
        std::cerr << "Error: Cannot open file " << filename << '\n';
        exit(0);
    }
    //ciclo spoletini
    file_in >> appo;
    while(!file_in.eof()){
        conta++;
        file_in >> appo;
    }

    file_in.clear();
    file_in.seekg(0,std::ios::beg);

    *size = conta;
    */
    data= new double[*size];

    for(int i=0;i<*size;i++){
        file_in >> data[i];
    }

    file_in.close();

    return data;

}



void ScambiaByValue(double a,double b){//non fa nulla
    double c = a;
    a = b;
    b = c;
}
void ScambiaByRef(double& a,double& b){
    double c = a;
    a = b;
    b = c;
}
void ScambiaByPointer(double *a, double *b){
    double c = *a;
    *a = *b;
    *b = c;
}

void selection_sort(double *data,int size){
    for(int j=0;j<size-1;j++){
        int imin=j;
        double min =data[imin];
        for(int i=j+1;i<size;i++){
            if(data[i]<min){
                min=data[i];
                imin=i;
            }
        }
        ScambiaByRef(data[j],data[imin]);
    }
}



double CalcolaMedia(double *data,int size){
    double accumulo =0;

    if(size == 0){
        return accumulo;
    }

    for(int i=0;i<size;i++){//evito di conservare la somma di tutti i valori per poi dividere
        accumulo = static_cast<double>(i)/static_cast<double>(i+1)*accumulo + 
        1.0/static_cast<double>(i+1)*data[i];
    }

    return accumulo;

}

double CalcolaVarianza(double *data,int size){
    double result=0;
    
    if(size == 0){
        return result;
    }

    double old_average;
    double average=0;

    for(int i=0;i<size;i++){ //evito di conservare la somma di tutti i valori
        old_average =average;
        average= static_cast<double>(i) / static_cast<double>(i+1)*average+
        1.0/static_cast<double>(i+1)*data[i];

        result = 1.0 / static_cast<double>(i+1)*
        (static_cast<double>(i)*result +
        data[i]*data[i] + static_cast<double>(i)*old_average*old_average) -
        average*average;

    }
    return result;
}





double CalcolaMediana(double *data,int size){
double * vcopy = new double[size];
for(int i=0;i<size;i++){
    vcopy[i] = data[i];
}

selection_sort(vcopy,size); //ordino l'array

double mediana =0;

if(size % 2 == 0){
    mediana = (vcopy[size/2-1]+vcopy[size/2])/2;
}else{
    mediana=vcopy[size/2];
}

delete[] vcopy;

return mediana;
    
}

void Print(const char*filename, double *data, int size){
    
    std::ofstream fout;

    fout.open(filename);

    for(int i=0;i<size;i++){
        fout << data[i] <<"\n";
    }

    fout <<"Media= " << std::setprecision(8) << CalcolaMedia(data,size)<< "\n";
    fout <<"Mediana= " << std::setprecision(8) << CalcolaMediana(data,size) << "\n";
    fout <<"Varianza= " << std::setprecision(8) << CalcolaVarianza(data,size) << "\n";

    fout.close();
    
}

void Print(const double*data,int size){
    for(int i=0;i<size;i++){
        std::cout << data[i] <<"\n";
    }
}
