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
    //selection_sort(v);
    merge_sort(v,0,v.GetN()-1);
    //quicksort(v,0,v.GetN()-1);
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

void merge_sort(Vettore &a,int low,int high){
    int mid;
    if(low<high) {
        mid = low + (high-low)/2; //This avoids overflow when low, high are too large
        merge_sort(a,low,mid);
        merge_sort(a,mid+1,high);
        merge(a,low,mid,high);
    }
}

//Questa funzione di merging è specializzata al caso in cui i vettori da fondere
//sono in realta` due sottovettori di un vettore individuati da tre indici:
//creato dinamicamente, a partire da due vettori distinti

void merge(Vettore &a,int low,int mid,int high){
    //low: indice piu` piccolo dell'array da fondere
    //mid: mezzo dell'array da fondere
    //high: indice piu` grande dell'array da fondere

    int h,i,j,k;
    h=low; //Indice libero per scandire vettore di sinistra
    i=0; //Indica la prima posizione libera dell'array in cui stiamo copiando i dati
    j=mid+1; //Indice libero per scandire vettore di destra

    double* b{new double[high-low+1]}; //Abbiamo bisogno di un vettore di appoggio dove copiare i dati


    while((h<=mid)&&(j<=high)){ //Mentre non hai esaurito uno dei due sottovettori
        if(a[h]<=a[j]){
            b[i]=a[h];
            h++; //Avanza di uno con l'indice libero dell'array di sinistra
        }
        else{
            b[i]=a[j];
            j++; //Avanza di uno con l'indice libero dell'array di destra
        }
        i++; //
    }

    if(h>mid){ //Se hai esaurito il sottovettore di sinistra, riversa in b quanto rimane del sottovettore di destra
        for(k=j;k<=high;k++){
            b[i]=a[k];
            i++;
        }
    }
    else{
        for(k=h;k<=mid;k++){ //Se hai esaurito il sottovettore di destra, riversa in b quanto rimane del sottovettore di sinistra
            b[i]=a[k];
            i++;
        }
    }

    i=0; //Reset indice vettore i per la copia
    //for(k=low;k<=high;k++,i++) a[k]=b[i]; //Ricopia in a il vettore ordinato b.
    memcpy(static_cast<void*>(a.data()+low),static_cast<void*>(b),sizeof(int)*(high-low+1));

    delete[] b;
}


void quicksort(Vettore& v, unsigned int left_bound,unsigned int right_bound)
{
    static std::random_device rndgen;

    int partition_size = right_bound - left_bound + 1;
    if (partition_size <= 1) return;  
    
    double max, min, median, pick;

    std::uniform_int_distribution<int> rndist(0,partition_size-1);

    // Choose a partition value with the "median-of-three" method.
    max = v[left_bound + rndist(rndgen)];
    min = v[left_bound + rndist(rndgen)];

    pick = v[left_bound + rndist(rndgen)];
    if (pick > max) max = pick;
    else if (pick < min) min = pick;

    pick = v[left_bound + rndist(rndgen)];
    if (pick > max) median = max;
    else if (pick < min) median = min;
    else median = pick;

    unsigned int i{},k{};

    for (i = left_bound, k = right_bound; ; i++,k--)
    {
    while (v[i] < median) i++;
    while (v[k] > median) k--;

    // Now stop if indexes crossed. This way we are sure that k is the
    // last element of the left partition. 
    if (i>=k) break;

    // We found a pair that's out of order. Let's swap them.
    double swap = v[i];
    v[i] = v[k];
    v[k] = swap;
    }

    // Operate recursively on the left and right sub-partitions.
    quicksort(v, left_bound, k);
    quicksort(v,k+1,right_bound);

    return;
}