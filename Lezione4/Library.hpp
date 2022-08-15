#include <iostream>
#include <fstream> 
#include <algorithm> 
#include <assert.h>
#include <numeric> 
#include <cmath>
#include <cstring>

#include <vector>
#include <iterator>


// =============================================================================
// Questa funzione legge N elementi da file e li carica in un vettore (c++11 !)
// =============================================================================

template <typename T> std::vector<T> Read( unsigned int N , const char* filename ) {

  std::ifstream in(filename);
  //  assert(  in && "Input file does not exist"  ) ;
  if ( !in ) {
    std::cout << "Cannot open file " << filename << '\n';
    exit(11);
  } 
  
  std::vector<T> v;
  std::copy_n ( std::istream_iterator<T>(in) , N, back_inserter(v) ); 
  //back_inserter inserisce l'elemento nel contenitore assicurandosi che ci sia sempre spazio

  std::cout<< "new Read: vector size = " << v.size() << '\n';
  
  in.close();
    
  return v;

};

// =============================================================================
// Questa funzione legge tutti gli elementi di un file e li carica in un vettore
// =============================================================================

template <typename T> std::vector<T> ReadAll( char* filename ) {
  
  std::ifstream in(filename);
  // assert(  in && "Input file does not exist"  ) ;
  if ( !in ) {
    std::cout << "Cannot open file " << filename << '\n';
    exit(11);
  } 

  std::vector<T> v ((std::istream_iterator<T>(in)) ,std::istream_iterator<T>()) ;

  //std::vector<T> v;
  //std::copy((std::istream_iterator<T>(in)) ,std::istream_iterator<T>(),back_inserter(v));

  std::cout<< " new ReadAll: vector size = " << v.size() << '\n';  
  
  in.close();
    
  return v;

};

// =============================================================================================
// Questa funzione legge i dati di file a 3 colonne e li inserisce in 3 vettori myx,myy e myerry
// =============================================================================================


void ParseFile( std::string filename, std::vector<double> & myx, std::vector<double> & myy , std::vector<double> & myerry ) {
  
  std::ifstream fin(filename.c_str());
  
  double x, y, err ;
  
  if ( !fin ) {
    std::cout << "Cannot open file " << filename << '\n';
    exit(11);
  };
  
  while ( fin >> x >> y >> err ) {
    myx.push_back(x);
    myy.push_back(y);
    myerry.push_back(err);    
  };

  std::cout<< " new ParseFile: vector size = " << myx.size() << " " << myy.size() << " " << myerry.size() << '\n';  
  
  
  fin.close();
}


// =============================================================================
// Questa funzione stampa gli elementi di un contenitore ( generico ! non solo
// vector ) a video
// =============================================================================

template <typename T> void Print( T _start , T _end ) {              
  for ( T it = _start; it != _end; it++ ) std::cout << *it << '\n';                                                
  std::copy(_start, _end, std::ostream_iterator<double>(std::cout, " "));
}                                                                          
 
// =============================================================================
// Questa funzione stampa gli elementi di un contenitore ( generico ! non solo
// vector ) su un file
// =============================================================================

template <typename T> void Print(  T _start , T _end  , char* filename ) {
  std::ofstream out(filename);
  if ( !out ) {
    std::cerr << "Non posso creare il file " << filename << '\n';
    exit(2);
  }
  std::copy( _start, _end, std::ostream_iterator< double >( out, '\n' ));
  out.close();
};

// =============================================================================
// Questa funzione calcola la media dei numeri in un contenitore
// =============================================================================

template <typename T> double CalcolaMedia( T _start , T _end ) { //utilizzo iteratori

  double accumulo{};
  
  for ( T it = _start; it != _end; it++ ) {
    accumulo += *it ;
  }

  return accumulo / static_cast<double>(_end-_start)  ;

};

// =============================================================================
// Meglio ancora : calcolo la media usando un accumulatore ( <numeric> )
// =============================================================================

template <typename T> double Media( T _start , T _end ) {

  return std::accumulate(_start, _end, 0.0) /  static_cast<double>(_end-_start)   ;

}

// =============================================================================
// Calcolo la mediana
// =============================================================================

template <typename T> double Mediana( std::vector<T> v ) {

  std::sort( v.begin(), v.end() ) ;  
  
  double mediana{};
  
  if ( v.size() %2 == 0 ) {    
    mediana = ( v[v.size() /2 -1 ] + v[ v.size()/2 ]  ) /2.;    
  } else {
    mediana = v[ v.size() /2 ];    
  }
  
  return mediana;

};

// =============================================================================
// Calcolo la varianza : uso accumulatori e prodotto interno ( <numeric> )
// =============================================================================

template <typename T> double Varianza( T _start , T _end ) {

double mean = std::accumulate(_start, _end , 0.0)  /  static_cast<double>(_end-_start)  ;

double sq_sum = std::inner_product(_start, _end, _start, 0.0);
return std::sqrt(sq_sum /static_cast<double>(_end-_start)   - mean * mean);

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